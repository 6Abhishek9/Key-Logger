# 🛡️ Windows Keylogger (Educational Use Only)

This is a simple keylogger built in C++ that logs keystrokes to a local file and sends them to a PHP server running on `localhost`. It's intended **only for educational and ethical testing purposes**.

## 📂 Project Structure

```
C:/Projects/c++/Keylogger/
├── keylogger.cpp         # C++ source code for the keylogger
├── receive.php           # PHP script to receive and store logged keys
├── received_log.txt      # Output file (created by receive.php)
├── keylog.txt            # Local log file (created by the keylogger)
```

## 🚀 Features

- Captures all keyboard input using Windows API
- Sends logs via HTTP POST to a PHP server (localhost)
- Stores logs in `received_log.txt`
- Hides the console window using `ShowWindow()`

## ⚙️ Requirements

- Windows OS
- PHP (no need for full XAMPP)
- MinGW with g++ installed
- Internet library (`-lwininet`)

## 🛠️ Setup Instructions

### 1. Install PHP

- Download from: https://windows.php.net/download/
- Extract to `C:\php`
- Test with: `C:\php\php.exe -v`

### 2. Prepare Project Folder

```bash
cd "C:\Projects\c++\Keylogger"
```

Create the files:

- `receive.php` (for receiving keylog data)
- `keylogger.cpp` (your source code)

### 3. Start Local PHP Server

```bash
C:\php\php.exe -S localhost:8000
```

### 4. Compile the Keylogger

```bash
g++ keylogger.cpp -o keylogger.exe -lwininet
```

### 5. Run the Keylogger

In PowerShell:

```bash
.\keylogger.exe
```

### 6. Test It

- Open Notepad, type anything
- Check `received_log.txt` for results

## ❗ Disclaimer

This tool is strictly for **educational** and **ethical testing** purposes.  
**Do not** deploy or use it on machines you do not own or without full permission.  
Unauthorized keylogging is illegal and unethical.

## 🧠 Credits

Made with ❤️ by Abhishek Kumar for personal learning and cybersecurity practice.
