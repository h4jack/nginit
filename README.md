
# nginit
A command-line application to create necessary files for running nginx on the current folder.
## Table of Contents
[About](#About)\
[Usage](#Usage)\
[Files and Directories](#Files-and-Directories)\
[Installation](#Installation)\
[Contributing](#Contributing)\
[License](#License)
## About

nginit is a simple command-line application that generates configuration files, logs, and temporary directories for a basic nginx setup. It is designed to make it easy to get started with nginx development.
## Usage/Examples

To use nginit, simply run the application in the terminal or command prompt. You can also pass arguments to customize the behavior.

- `nginit`: Creates all necessary files and directories for a basic nginx setup.
- `nginit` -h` or `nginit --help`: Displays the help message with usage instructions.
- `nginit -v` or `nginit --version`: Displays the version number of nginit.


## Files and Directories
nginit creates the following files and directories:
- `conf/`: A directory containing configuration files for nginx.
- `conf/nginx.conf`: The main configuration file for nginx.
- `conf/fastcgi_params`: A file containing FastCGI parameters.
- `conf/fastcgi.conf`: A file containing FastCGI configuration.
- `conf/koi-utf`: A file containing KOI8-U to UTF-8 mapping.
- `conf/koi-win`: A file containing KOI8-R to Windows-1251 mapping.
- `conf/mime.types`: A file containing MIME types for nginx.
- `conf/scgi_params`: A file containing SCGI parameters.
- `conf/uwsgi_params`: A file containing uWSGI parameters.
- `conf/win-utf`: A file containing Windows-1251 to UTF-8 mapping.
- `html/`: A directory containing HTML files.
- `html/index.html`: A basic HTML file for testing nginx.
- `logs/`: A directory containing log files.
- `logs/access.log`: A file for access logs.
- `logs/error.log`: A file for error logs.
- `temp/`: A directory containing temporary files.
- `temp/client_body_temp/`: A directory for client body temporary files.
- `temp/fastcgi_temp/`: A directory for FastCGI temporary files.
- `temp/proxy_temp/`: A directory for proxy temporary files.
- `temp/scgi_temp/`: A directory for SCGI temporary files.
- `temp/uwsgi_temp/`: A directory for uWSGI temporary files.
## Installation

To install nginit, simply clone the repository and compile the code.

```bash
git clone https://github.com/h4jack/nginit.git
cd nginit
gcc nginit.c -o nginit
```
    
## Contributing

Contributions are always welcome! If you find any issues or have suggestions, please open an issue or submit a pull request.


## License

License
nginit is licensed under the [MIT License](https://github.com/h4jack/nginit/license.md/). See the LICENSE file for details.


## 🔗 Links
[![portfolio](https://img.shields.io/badge/my_portfolio-000?style=for-the-badge&logo=ko-fi&logoColor=white)](https://susanta.rf.gd/)
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/susantamandi/)
[![twitter](https://img.shields.io/badge/twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/susantamandi)

