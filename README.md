# CBDC Transaction Processor

Central Banking Digital Currency Transaction Processor.

## Table of Contents

- [Development](#hammer_and_wrench-development)
    - [Prerequisites](#package-prerequisites)
    - [Libraries](#books-libraries)
        - [Downloads](#downloading--extracting-source-files)
        - [Installing Boost](#build-and-install-boost)
        - [Installing nlohmann-json](#install-nlohmann-json)
    - [Build Configuration](#gear-build-configuration)
- [Testing](#bug-testing)
    - [Virtual Machines](#computer-virtual-machines)
        - [Shared Host](#shared-host)
- [Deployment](#rocket-deployment)
- [License](#page_with_curl-license)

## :hammer_and_wrench: Development

:exclamation: Instructions for Debian-based Linux Distributions.

### :package: Prerequisites

Installing Dependencies:

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get upgrade
sudo apt-get install cmake
sudo apt-get install g++
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

### :books: Libraries

#### Downloading & Extracting Source Files:

- Download the latest releases:\
Boost: [boost.org/users/download/](url) &nbsp; | &nbsp; nholmann-json: [github.com/nlohmann/json/releases](url)

    The Source Code is usually available in a Compressed Archive Format (e.g., .zip, .tar.gz) like **boost_X_YY_Z.tar.gz** and **json-x.y.z.tar.gz**

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

- Copy the Header File to `/usr/local/include`:

    ```bash
    sudo mkdir -p /usr/local/include/nlohmann/
    sudo cp json-x.y.z/single_include/nlohmann/json.hpp /usr/local/include/nlohmann/
    ```

    You can replace `/usr/local/include` with `/your/installation/path`.

- Verify the Installation:

    ```bash
    cat /usr/local/include/nlohmann/json.hpp | grep "NLOHMANN_JSON_VERSION"
    ```

### :gear: Build Configuration

- Create a Build Directory:

    ```bash
    mkdir build
    cd build
    ```

- Run CMake to Configure the build:

    ```bash
    cmake ..
    make
    ```

    Notice the **transmit** and **listen** executables in the build directory.

## :bug: Testing

The system can be readily tested on the Loopback address. Just set the **TRANSMITTER_IP** and **LISTENER_IP** directives in the source files to `127.0.0.1` and you should be able to simulate the network communication by running the executables in separate terminal windows.

### :computer: Virtual Machines

#### Shared Host

Test communication between VirtualBox VMs with a shared Host.

- Add Host-Only Network Adapters to both VMs
- Find the `enp0s3` network interface and check its IPv4 address as indicated by the **inet** tag. Use `ipconfig` or `ip addr show` to list the up interfaces.
  
- Set the **LISTENER_IP** directive to the IP address of the target VM and the **TRANSMITTER_IP** directive to the IP address of the source VM.

    :exclamation: Configuration might vary depending on the virtualization platform.

## :rocket: Deployment



## :page_with_curl: License

Distributed under the MIT License. See `LICENSE.txt` for more information.