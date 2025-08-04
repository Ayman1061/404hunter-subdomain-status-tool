#include <iostream>
#include <string>
#include <regex>
#include <filesystem>
#include <fstream>
#include <thread>
#include <boost/asio.hpp>
#include <mutex>

bool is_alive(std::string subdomain, int timeout_ms, bool http_only) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::steady_timer timer(io_context);
    bool connected_http = false;
    if (http_only || !http_only) {
        bool done = false;
        try {
            auto endpoints = resolver.resolve(subdomain, "80");
            timer.expires_after(std::chrono::milliseconds(timeout_ms));
            timer.async_wait([&](boost::system::error_code ec) {
                if (!ec && !done) {
                    socket.cancel();
                }
                });
            async_connect(socket, endpoints,
                [&](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
                    done = true;
                    if (!ec) {
                        connected_http = true;
                        timer.cancel();
                    }
                });
            io_context.run();
        }
        catch (...) {

        }
    }
    if (!http_only) {
        bool done = false;
        try {
            auto endpoints = resolver.resolve(subdomain, "443");
            timer.expires_after(std::chrono::milliseconds(timeout_ms));
            timer.async_wait([&](boost::system::error_code ec) {
                if (!ec && !done) {
                    socket.cancel();
                }
                });
            async_connect(socket, endpoints,
                [&](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
                    done = true;
                    if (!ec) {
                        connected_http = true;
                        timer.cancel();
                    }
                });
            io_context.run();
        }
        catch (...) {

        }
    }
    return connected_http;
}

std::string help() {
    return
        "Help Section\n"
        "-------------------------\n"
        "1. File Options\n"
        "  +-- -f, --file <file>\n"
        "  |    +-- Provide a .txt file with subdomains to check.\n"
        "  +-- -o, --output <output>\n"
        "  |    +-- Specify the output file to save the results (must have a .txt extension).\n"
        "  |    +-- If no extension is provided, '.txt' will be added automatically.\n"
        "\n"
        "2. Threading & Timeout\n"
        "  +-- -T, --threads <threads>\n"
        "  |    +-- Set the number of threads to use for subdomain checking.\n"
        "  |    +-- Default is 1. Max threads: (CPU cores * 4).\n"
        "  +-- -t, --timeout <timeout>\n"
        "  |    +-- Set the timeout in seconds for each subdomain check.\n"
        "  |    +-- Valid range: 1 to 60 seconds. Default is 1 second.\n"
        "\n"
        "3. HTTP/HTTPS Options\n"
        "  +-- --http-only\n"
        "  |    +-- Only check for HTTP (port 80) for subdomains. Ignores HTTPS (port 443).\n"
        "\n"
        "4. Verbose Mode\n"
        "  +-- -v, --verbose\n"
        "  |    +-- Enable verbose output to show dead subdomains as well.\n"
        "\n"
        "5. Help\n"
        "  +-- -h, --help\n"
        "  |    +-- Displays this help section.\n"
        "-------------------------\n";
}

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int thread_count = 1;
    int timeout = 1;
    int timeout_ms = timeout * 1000;
    std::string file_path;
    std::string outfile_path;

    bool http_only = false;
    bool arg_f = false;
    bool arg_v = false;
    bool arg_o = false;


    if (argc == 1) {
        std::cout << help() << '\n';
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << help() << '\n';
            return 0;
        }

        else if (arg == "-f") {
            arg_f = true;
            if (i + 1 < argc) {
                file_path = argv[++i];

                std::regex file_pattern(R"(.*\.txt$)");
                if (!std::regex_match(file_path, file_pattern)) {
                    std::cerr << "[!] Please provide a .txt file.\n";
                    return 1;
                }

                if (!std::filesystem::exists(file_path)) {
                    std::cerr << "[!] File does not exist: " << file_path << '\n';
                    return 1;
                }

            }
            else {
                std::cerr << "[!] Missing file path after -f flag.\n";
                return 1;
            }
        }

        else if (arg == "-T" || arg == "--threads") {
            if (i + 1 < argc) {
                std::string thread_str = argv[++i];
                bool valid_thread = true;
                for (char c : thread_str) {
                    if (!std::isdigit(c)) {
                        valid_thread = false;
                        break;
                    }
                }
                if (valid_thread) {
                    thread_count = std::stoi(thread_str);
                }
                else {
                    std::cerr << "[!] Invalid thread count: " << thread_str << '\n';
                    return 1;
                }
                int max_threads = std::thread::hardware_concurrency() * 4;
                if (thread_count < 1 || thread_count > max_threads) {
                    std::cerr << "[!] Thread count must be between 1 and " << max_threads << " (max threads).\n";
                    return 1;
                }
            }
            else {
                std::cerr << "[!] Missing value after " << arg << '\n';
                return 1;
            }
        }

        else if (arg == "-o" || arg == "--output") {
            arg_o = true;
            if (i + 1 < argc) {
                std::string isvalid_output = argv[++i];
                if (isvalid_output == "." || isvalid_output == " ") {
                    std::cerr << "[!] Invalid output filename\n";
                    return 1;
                }
                size_t output_dot = isvalid_output.find_last_of('.');
                if (output_dot != std::string::npos) {
                    std::string output_ext = isvalid_output.substr(output_dot);
                    std::transform(output_ext.begin(), output_ext.end(), output_ext.begin(), ::tolower);
                    if (output_ext == ".txt") {
                        outfile_path = isvalid_output;
                    }
                    else {
                        std::cerr << "[!] Invalid extension '" << output_ext << "'. Only .txt is allowed.\n";
                        return 1;
                    }
                    for (char c : outfile_path) {
                        std::string invalidChars = "\\/:*?\"<>|";
                        if (invalidChars.find(c) != std::string::npos) {
                            std::cerr << "[!] Output filename contains invalid character: '" << c << "'\n";
                            return 1;
                        }
                    }
                }
                else {
                    outfile_path = isvalid_output + ".txt";
                }
            }
            else {
                std::cerr << "[!] Missing output path after " << arg << '\n';
                return 1;
            }
        }

        else if (arg == "--http-only") {
            http_only = true;
        }

        else if (arg == "-t" || arg == "--timeout") {
            if (i + 1 < argc) {
                std::string timeout_str = argv[++i];
                bool valid_time = true;
                for (char c : timeout_str) {
                    if (!isdigit(c)) {
                        valid_time = false;
                        break;
                    }
                }
                if (valid_time) {
                    timeout = std::stoi(timeout_str);
                }
                else {
                    std::cerr << "[!] Invalid timeout: " << timeout_str << '\n';
                    return 1;
                }

                if (timeout < 1 || timeout > 60) {
                    std::cerr << "[!] Timeout must be between 1 and 60 seconds.\n";
                    return 1;
                }
            }
            else {
                std::cerr << "[!] Missing value after " << arg << '\n';
                return 1;
            }
        }

        else if (arg == "-v" || arg == "--verbose") {
            arg_v = true;
        }

        else {
            std::cerr << "[!] Unknown argument: " << arg << '\n';
            return 1;
        }
    }

    if (arg_f == false) {
        std::cerr << "[!] -f is required\n";
        return 1;
    }



    std::ifstream open_file(file_path);
    if (!open_file.is_open()) {
        std::cerr << "[!] Failed to open file: " << file_path << '\n';
        return 1;
    }
    std::string line;
    std::vector<std::string> subdomains;
    while (std::getline(open_file, line)) {
        if (line.empty()) {
            continue;
        }
        subdomains.push_back(line);
    }
    if (subdomains.empty()) {
        std::cerr << "[!] File is empty or contains no valid subdomains.\n";
        return 1;
    }

    int subdomains_per_thread = (subdomains.size() + thread_count - 1) / thread_count;
    std::vector<std::thread> threads;
    std::mutex cout_mutex;
    std::vector<std::string> output_content;
    for (int i = 0; i < thread_count; ++i) {
        int start = i * subdomains_per_thread;
        int end = std::min(start + subdomains_per_thread, static_cast<int>(subdomains.size()));


        threads.push_back(std::thread([=, &subdomains, &cout_mutex, &output_content]() {
            for (int j = start; j < end; ++j) {
                std::string sub = subdomains[j];
                bool alive = is_alive(sub, timeout_ms, http_only);

                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    if (alive) {
                        std::cout << "[+] Alive: " << sub << '\n';
                        output_content.push_back(sub);
                    }
                    else if (arg_v) {
                        std::cout << "[-] Dead: " << sub << '\n';
                    }
                }
            }
            }));
    }
    for (auto& t : threads) {
        t.join();
    }

    if (arg_o) {
        std::ofstream output_file(outfile_path);
        if (!output_file) {
            std::cerr << "Failed to open file: " << outfile_path << std::endl;
            return 1;
        }
        for (std::string line : output_content) {
            output_file << line << '\n';
        }
        output_file.close();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "\n[!] Time taken: " << duration.count() << " seconds.\n";

    return 0;
}