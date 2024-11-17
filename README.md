# ScanTheNet-Cplusplus
C++ API Data Fetcher.

This project is a C++ application that retrieves and displays data from our API endpoint using the **libcurl** library for HTTP(S) requests and the **nlohmann/json** library for JSON parsing. 

## Features

- **API Interaction**: Makes GET requests to our API endpoint and retrieves JSON data.
- **Dynamic Entry Limit**: Users can specify the maximum number of data entries to display (up to 100).

## Requirements

- **C++ Compiler**: Ensure you have a C++ compiler like g++.
- **libcurl**: Install `libcurl` for handling HTTP requests.
- **nlohmann/json**: Include the nlohmann JSON library, either by installing it or including the header file.

## Installation

### Install Dependencies

For Debian-based systems, you can install the required libcurl development files using:

```
apt install libcurl4-openssl-dev
```

Clone the Repository

```
git clone https://github.com/ScanThe-Net/ScanTheNet-Cplusplus.git
cd ScanTheNet-Cplusplus
```

Compile

```
g++ -o scanthenet scanthenet.cpp -I include -lcurl
```

Usage

Run it from the command line. Optionally, you can specify the maximum number of entries:

```
./scanthenet [maxEntries]
```

Replace [maxEntries] with a number between 1 and 100. If not specified, the default value is 100.

Example Output

When executed successfully, it will display results in the following format:

```
ID: 123
Timestamp: 2023-10-05T12:34:56Z
Source IP: 192.168.0.1
Source Port: 8080
Destination Port: 80
Data: Sample data
----------
```
