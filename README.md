# CBDC Transaction Processor

## Table of Contents

- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
- [License](#license)

## Getting Started

Instructions for Debian-based Linux Distributions.

### Prerequisites

Installing Dependencies:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

### Installation

#### Downloading & Extracting Source Files:

Download the latest release from https://www.boost.org/users/download/

The Source Code is usually available in a Compressed Archive Format (e.g., .zip, .tar.gz) like *boost_X_YY_Z.tar.gz*

Extract the Source Code and Navigate to Extracted Directory:

```bash
tar -xzvf boost_X_YY_Z.tar.gz
cd boost_X_YY_Z
```
#### Build and Install Boost:

Prepare Boost for Building:

```bash
sudo ./bootstrap.sh
```

Boost C++ Libraries are a collection of individual libraries. You can choose to build only the specific libraries you need by using `--with-libraries` option as follows:

```bash
sudo ./bootstrap.sh --with-libraries=<library1,library2,...>
```

Install Boost Libraries:

```bash
sudo ./b2 install
```

The default installation path is often `/usr/local`. You can specify the installation path using the `--prefix` option as follows:

```bash
sudo ./b2 install --prefix=/your/installation/path
```

Verify the Installation:

```bash
cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
```

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.