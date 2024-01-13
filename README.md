# CBDC Transaction Processor

## Table of Contents

- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
        - [Downloads](#downloading--extracting-source-files)
        - [Installing Boost](#build-and-install-boost)
        - [Installing nlohmann-json](#install-nlohmann-json)
- [License](#license)

## Getting Started

Instructions for Debian-based Linux Distributions.

### Prerequisites

Installing Dependencies:

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get upgrade
```

\[Optional]

Installing **vcpkg**:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

Integrate with Bash:

```bash
echo 'export PATH=$PATH:/path/to/vcpkg' >> ~/.bashrc
```

Replace `/path/to/vcpkg` with the actual path to your vcpkg directory.

### Installation

#### Downloading & Extracting Source Files:

- Download the latest releases:\
Boost: https://www.boost.org/users/download/ nholmann-json: https://github.com/nlohmann/json/releases

    The Source Code is usually available in a Compressed Archive Format (e.g., .zip, .tar.gz) like *boost_X_YY_Z.tar.gz* and *json-x.y.z.tar.gz*

- Extract the Source Code Files:

    ```bash
    tar -xzvf boost_X_YY_Z.tar.gz
    tar -xzvf json-x.y.z.tar.gz
    ```

#### Build and Install Boost:

- Navigate to Extracted Directory:

    ```bash
    cd boost_X_YY_Z
    ```

- Prepare Boost for Building:

    ```bash
    sudo ./bootstrap.sh
    ```

    Boost C++ Libraries are a collection of individual libraries. You can choose to build only the specific libraries you need by using `--with-libraries` option as follows:

    ```bash
    sudo ./bootstrap.sh --with-libraries=<library1,library2,...>
    ```

- Install Boost Libraries:

    ```bash
    sudo ./b2 install
    ```

    The default installation path is often `/usr/local`. You can specify the installation path using the `--prefix` option as follows:

    ```bash
    sudo ./b2 install --prefix=/your/installation/path
    ```

- Verify the Installation:

    ```bash
    cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
    ```

#### Install nlohmann-json

- Copy the header file to `/usr/local/include`:

    ```bash
    sudo mkdir -p /usr/local/include/nlohmann/
    sudo cp json-x.y.z/single_include/nlohmann/json.hpp /usr/local/include/nlohmann/
    ```

    You can replace `/usr/local/include` with `/your/installation/path`.

- Verify the Installation:

    ```bash
    cat /usr/local/include/nlohmann/json.hpp | grep "NLOHMANN_JSON_VERSION"
    ```

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.