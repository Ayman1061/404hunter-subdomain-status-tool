# 404hunter: Subdomain Health Checker

404hunter is a fast, multi-threaded tool designed to check the availability of subdomains using HTTP (port 80) and HTTPS (port 443).
Whether you're a security researcher, developer, or sysadmin, 404hunter helps you quickly determine if your subdomains are alive or dead.

🚀 **Features**
- Multi-threaded subdomain checking for faster results.
- Check subdomains via HTTP (port 80) and HTTPS (port 443).
- Adjustable timeout for each request (from 1 to 60 seconds).
- HTTP-only mode to check only port 80.
- Verbose mode to show dead subdomains.
- Output results to a file for further processing.

🔧 **Installation**
Clone the repository to your local machine:

```bash
git clone https://github.com/0xhex0rc1st/404hunter-subdomain-status-tool.git
````

Compile the project using your preferred build system (e.g., `g++`, `CMake`).

🧾 **Usage**
Run 404hunter with the following command:

```bash
./404hunter [OPTIONS]
```

### Main Options:

* `-f <file>` or `--file <file>`
  Specifies the path to a `.txt` file containing a list of subdomains to check.

* `-o <output>` or `--output <output>`
  Specifies the output file where the results will be saved (must end with `.txt`).

* `-T <threads>` or `--threads <threads>`
  Set the number of threads to use for checking subdomains (default is 1, max is based on CPU cores).

* `-t <timeout>` or `--timeout <timeout>`
  Set the timeout in seconds for each subdomain check (valid range: 1 to 60, default is 1 second).

* `--http-only`
  Only check HTTP (port 80), ignoring HTTPS (port 443).

* `-v` or `--verbose`
  Enable verbose mode to show dead subdomains.

* `-h` or `--help`
  Display the help message with all available options.

🔍 **Examples**

* Check a list of subdomains from a file:

  ```bash
  ./404hunter --file subdomains.txt --output results.txt
  ```

* Check subdomains using 4 threads:

  ```bash
  ./404hunter --file subdomains.txt --threads 4
  ```

* Check subdomains with a custom timeout of 3 seconds:

  ```bash
  ./404hunter --file subdomains.txt --timeout 3
  ```

* Enable verbose mode to see dead subdomains:

  ```bash
  ./404hunter --file subdomains.txt --verbose
  ```

💡 **Tips**

* Want faster results? Use more threads (`-T <number>`) to speed up checking in large subdomain lists.
* Need to only check HTTP? Use the `--http-only` flag to ignore HTTPS.
* Save the results to a file with the `-o` option for later review.
