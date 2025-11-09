# Câu lệnh github
- git init : tạo file ẩn git chứa tất cả lịch sử commit,... trên máy
- git remote add origin https://github.com/anhtus-304/CTDL.git : kết nối với repon
- git clone origin https://github.com/anhtus-304/CTDL.git : clone code từ repon về máy
- git fetch origin : cập nhật tất cả các nhánh trên repon
- git branch -a : liệt kê các nhánh trên máy
- git switch -c <tên nhánh> : tạo nhánh và chuyển sang nhánh mới
- git switch <tên nhánh> : chuyển nhánh
- git add . & git commit -m "nội dung cập nhật" : chọn toàn bộ file đã thay đổi và lưu lại chúng vào một mốc lịch sử mới với lời nhắn mô tả
- git pull : cập nhật mọi thứ từ nhánh đang đứng trên máy
- git push origin <tên nhánh> / git push : đẩy tất cả đã làm trên máy lên nhánh đang đứng trên repon

# CTDL – Dự án quản lý thư viện (C++17)

## 1. Yêu cầu môi trường (Windows)
| Thành phần | Mô tả |
|------------|------|
| MSYS2      | Cài tại `C:\msys64` (https://www.msys2.org) |
| Gói        | `make`, `gcc` (`pacman -S --needed make gcc`) |
| PowerShell | Khuyên dùng để chạy script build/run |

Sau khi cài MSYS2: mở "MSYS2 UCRT64" shell và cài gói:
```bash
pacman -S --needed make gcc
```

## 2. Build & Run nhanh (script khuyến nghị)
Các script ở `scripts/` tự thiết lập PATH và UTF-8.

### Build
```powershell
./scripts/build.ps1            # build mặc định (target build/main.exe)
./scripts/build.ps1 clean      # dọn build
./scripts/build.ps1 -v         # ví dụ: truyền tham số (nếu có thêm rule)
```

### Run
```powershell
./scripts/run.ps1
```

## 3. Build & Run thủ công (không dùng script)
```powershell
$env:Path = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;" + $env:Path
C:\msys64\usr\bin\make.exe -C d:\DS_library\CTDL

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
cd d:\DS_library\CTDL
./build/main.exe

C:\msys64\usr\bin\make.exe -C d:\DS_library\CTDL clean
```

## 4. Cấu trúc Makefile
- Tự động quét toàn bộ `src/**/*.cpp`
- Sinh `build/main.exe`
- Có các target: `all`, `run`, `clean`
- Có thể override biến qua môi trường: `CXX`, `MKDIR`, `RM`

Ví dụ override compiler:
```powershell
$env:CXX = "clang++"; ./scripts/build.ps1
```

## 5. Dữ liệu & đăng nhập
- File tài khoản quản trị: `data/Admin.txt`
- Định dạng mỗi dòng: `username,password`
- Mặc định đã seed: `admin,admin123`
- Nếu muốn thêm admin mới: mở file và thêm dòng mới.


## 7. Troubleshooting (Sự cố thường gặp)
| Vấn đề | Nguyên nhân | Cách xử lý |
|--------|-------------|-----------|
| `make: g++: command not found` | Chưa cài gcc hoặc PATH chưa thêm `ucrt64/bin` | Cài `gcc`, thiết lập PATH như phần thủ công |
| Không đọc được `Admin.txt` | Sai working directory hoặc file rỗng | Chạy bằng `run.ps1`, kiểm tra nội dung file, thêm tài khoản |
| Ký tự tiếng Việt lỗi | Console encoding khác UTF-8 | Thiết lập `[Console]::OutputEncoding = [System.Text.Encoding]::UTF8` trước khi chạy |
| Clean báo lỗi `rm` | Thiếu coreutils trong PATH | Thêm `C:\msys64\usr\bin` vào PATH |


## 9. Licence
Hiện chưa khai báo. Nên thêm (ví dụ MIT) nếu public repo.

---
**Quick Cheatsheet:**
```powershell
# Build nhanh
./scripts/build.ps1

# Run
./scripts/run.ps1

# Clean
./scripts/build.ps1 clean
```

