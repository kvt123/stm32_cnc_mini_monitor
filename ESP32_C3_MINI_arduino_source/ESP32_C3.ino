#include <WiFi.h>
#include <WebServer.h>
#include <SD.h>
#include <SPI.h>
#include <esp_wifi.h> 
#include <dirent.h>      // Thư viện Lõi C để quét thư mục tầng thấp
#include <sys/stat.h>    // Thư viện Lõi C để đọc dung lượng file

// --- CẤU HÌNH WIFI ---
const char* ap_ssid = "CNC_WIFI";
const char* ap_password = "12345678";

// --- CẤU HÌNH CHÂN ---
#define MUX_CTRL_1 2
#define MUX_CTRL_2 3
#define SD_SCK     4
#define SD_MISO    5
#define SD_MOSI    6
#define SD_CS      7

#define STM_TX_PIN 1   
#define STM_RX_PIN 0   

WebServer server(80);
File uploadFile;

bool is_sd_controlled_by_wifi = false; 

// --- GIAO DIỆN HTML ---
const char* htmlHomePage = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CNC Gcode Manager</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; background-color: #f4f4f9; text-align: center; }
        .container { max-width: 600px; margin: auto; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
        .status-box { padding: 15px; margin-bottom: 20px; border-radius: 5px; font-weight: bold; }
        .bg-red { background-color: #f8d7da; color: #721c24; border: 1px solid #f5c6cb; }
        .bg-green { background-color: #d4edda; color: #155724; border: 1px solid #c3e6cb; }
        button { color: white; border: none; padding: 10px 20px; cursor: pointer; border-radius: 5px; font-size: 16px; margin: 5px; font-weight: bold; }
        .btn-blue { background-color: #007bff; } .btn-blue:hover { background-color: #0056b3; }
        .btn-orange { background-color: #fd7e14; } .btn-orange:hover { background-color: #e86e10; }
        .btn-refresh { background-color: #28a745; margin-bottom: 10px; font-size: 14px;} .btn-refresh:hover { background-color: #218838; }
        .btn-delete { background-color: #dc3545; padding: 5px 10px; font-size: 12px; }
        ul { list-style-type: none; padding: 0; text-align: left; max-height: 400px; overflow-y: auto; border: 1px solid #ddd; border-radius: 4px; }
        li { background: #eee; margin: 5px; padding: 10px; border-radius: 4px; display: flex; justify-content: space-between; align-items: center; border-bottom: 1px solid #ddd;}
        #fileManager { display: none; margin-top: 20px; border-top: 2px solid #ddd; padding-top: 20px;}
    </style>
</head>
<body>
    <div class="container">
        <h2>🚀 Quản Lý Máy CNC qua Wi-Fi</h2>
        
        <div id="statusBox" class="status-box bg-red">Đang kiểm tra trạng thái...</div>
        
        <button id="btnTake" class="btn-blue" onclick="takeControl()" style="display:none;">📲 Kết nối Thẻ SD vào Wi-Fi</button>
        <button id="btnRelease" class="btn-orange" onclick="releaseControl()" style="display:none;">🖥️ Trả Thẻ SD cho CNC</button>

        <div id="fileManager">
            <iframe name="hidden_iframe" id="hidden_iframe" style="display:none;"></iframe>
            <form action="/upload" method="POST" enctype="multipart/form-data" target="hidden_iframe" onsubmit="startUpload()" style="margin-bottom: 10px;">
                <input type="file" id="fileInput" name="update" required>
                <button type="submit" class="btn-blue" id="uploadBtn">Tải File Lên</button>
            </form>
            
            <hr style="border: 1px solid #eee; margin: 20px 0;">
            <div style="display: flex; justify-content: space-between; align-items: center;">
                <h3 style="margin: 0;">Danh sách File trong thẻ:</h3>
                <button class="btn-refresh" onclick="loadFiles(true)">🔄 Quét Lại Thẻ Nhớ</button>
            </div>
            <div id="fileList">Đang tải...</div>
        </div>
    </div>

    <script>
        let isListLoaded = false;

        function checkStatus() {
            fetch('/status').then(res => res.text()).then(state => {
                if(state === "WIFI") {
                    document.getElementById('statusBox').className = "status-box bg-green";
                    document.getElementById('statusBox').innerHTML = "✅ Wi-Fi đang kiểm soát thẻ nhớ";
                    document.getElementById('btnTake').style.display = "none";
                    document.getElementById('btnRelease').style.display = "inline-block";
                    document.getElementById('fileManager').style.display = "block";
                    
                    if(!isListLoaded) loadFiles(false);
                } else {
                    document.getElementById('statusBox').className = "status-box bg-red";
                    document.getElementById('statusBox').innerHTML = "🔒 Màn hình CNC đang kiểm soát thẻ nhớ";
                    document.getElementById('btnTake').style.display = "inline-block";
                    document.getElementById('btnRelease').style.display = "none";
                    document.getElementById('fileManager').style.display = "none";
                    
                    isListLoaded = false; 
                }
            });
        }

        function takeControl() {
            document.getElementById('statusBox').innerHTML = "⏳ Đang xin quyền từ CNC...";
            fetch('/take').then(res => res.text()).then(res => {
                if(res === "OK") {
                    isListLoaded = false;
                    checkStatus();
                }
                else { alert("Lỗi: Màn hình CNC không phản hồi!"); checkStatus(); }
            });
        }

        function releaseControl() {
            fetch('/release').then(() => checkStatus());
        }

        function loadFiles(deepScan = false) {
            document.getElementById('fileList').innerHTML = "⏳ Đang quét thẻ nhớ (Chế độ POSIX Core)...";
            let targetUrl = deepScan ? '/refresh_sd' : '/list';
            
            fetch(targetUrl + '?t=' + new Date().getTime())
            .then(res => {
                if(!res.ok) throw new Error("Thẻ nhớ lỗi!");
                return res.text();
            })
            .then(data => { 
                document.getElementById('fileList').innerHTML = data; 
                isListLoaded = true; 
            })
            .catch(err => {
                document.getElementById('fileList').innerHTML = "<b style='color:red;'>❌ Không thể đọc thẻ nhớ.</b>";
            });
        }

        function deleteFile(filename) {
            if(confirm("Xóa file " + filename + "?")) {
                fetch('/delete?file=' + filename, { method: 'DELETE' }).then(() => loadFiles(false)); 
            }
        }

        function startUpload() {
            document.getElementById('uploadBtn').innerHTML = "Đang tải lên...";
            document.getElementById('uploadBtn').disabled = true;
        }

        window.uploadComplete = function() {
            document.getElementById('uploadBtn').innerHTML = "Tải File Lên";
            document.getElementById('uploadBtn').disabled = false;
            document.getElementById('fileInput').value = ""; 
            loadFiles(false); 
        };
        
        setInterval(checkStatus, 3000); 
        window.onload = checkStatus;
    </script>
</body>
</html>
)rawliteral";

void handleRoot() { server.send(200, "text/html", htmlHomePage); }

void handleStatus() {
    if (is_sd_controlled_by_wifi) server.send(200, "text/plain", "WIFI");
    else server.send(200, "text/plain", "CNC");
}

void handleTakeControl() {
    while(Serial1.available()) Serial1.read(); 
    Serial1.print("WIFI_REQ\n");
    
    // 3. Đợi phản hồi bằng hàm chuẩn (Timeout 3 giây)
    Serial1.setTimeout(3000);
    String response = Serial1.readStringUntil('\n');

    if (response.indexOf("WIFI_ACK") != -1) {
        // LÚC NÀY STM32 ĐÃ GẠT MUX XONG XUÔI, ESP32 CHỈ VIỆC DÙNG
        delay(100); 
        
        SD.end();
        SPI.end();
        
        SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
        if (SD.begin(SD_CS, SPI, 4000000)) { 
            is_sd_controlled_by_wifi = true;
            server.send(200, "text/plain", "OK");
        } else {
            server.send(200, "text/plain", "SD_ERROR");
        }
    } else {
        Serial.println("[LỖI] STM32 Không gửi WIFI_ACK. Phản hồi nhận được: " + response);
        server.send(200, "text/plain", "TIMEOUT");
    }
}

void handleReleaseControl() {
    if (is_sd_controlled_by_wifi) {
        SD.end(); 
        SPI.end(); 
        
        
        // --- THÊM LOGIC CHỜ PHẢN HỒI (HANDSHAKE) ---
        while(Serial1.available()) Serial1.read();
        Serial1.print("WIFI_REL\n");
        
        Serial1.setTimeout(3000);
        String response = Serial1.readStringUntil('\n');
        
        is_sd_controlled_by_wifi = false;
        
        if (response.indexOf("WIFI_REL_ACK") != -1) {
            server.send(200, "text/plain", "OK");
        } else {
            Serial.println("[CẢNH BÁO] STM32 Không gửi WIFI_REL_ACK.");
            server.send(200, "text/plain", "NO_ACK"); // Báo lỗi nhẹ cho Web
        }
    } else {
        server.send(200, "text/plain", "OK"); // Đã nhả từ trước
    }
}

// =======================================================================
// HÀM QUÉT THẺ NHỚ BẰNG LÕI POSIX C (BỎ QUA THƯ VIỆN LỖI CỦA ARDUINO)
// =======================================================================
void handleFileList() {
    if (!is_sd_controlled_by_wifi) { server.send(500, "text/plain", "Chua ket noi SD!"); return; }
    
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); 
    
    String htmlBuffer = "<ul>";
    
    // Mở thư mục gốc của thẻ SD (/sd) ở tầng thấp nhất
    DIR *dir = opendir("/sd");
    if (!dir) {
        server.sendContent("<li><b>Lỗi: Không thể mở thẻ nhớ (POSIX Error)!</b></li></ul>");
        server.sendContent(""); 
        return;
    }
    
    struct dirent *ent;
    int fileCount = 0;
    
    // Đọc liên tục từng tệp tin
    while ((ent = readdir(dir)) != NULL) {
        String filename = String(ent->d_name);
        
        // Bỏ qua các thư mục giả của hệ thống
        if (filename == "." || filename == "..") continue;
        
        // Bỏ qua rác của Windows / Mac
        if (filename.indexOf("System Volume Information") != -1 || filename.startsWith(".")) continue;
        
        // Dùng sys/stat.h để kiểm tra đây là File hay Thư mục con
        struct stat st;
        String fullPath = "/sd/" + filename;
        stat(fullPath.c_str(), &st);
        
        if (S_ISDIR(st.st_mode)) {
            // Là thư mục con -> Bỏ qua không hiển thị
            continue; 
        }
        
        htmlBuffer += "<li><span>📄 " + filename + " (" + String(st.st_size / 1024) + " KB)</span>";
        htmlBuffer += "<button class='btn-delete' onclick=\"deleteFile('/" + filename + "')\">Xóa</button></li>";
        fileCount++;
        
        // Đẩy dữ liệu ra ngoài web để tránh tràn RAM
        if (htmlBuffer.length() > 1024) {
            server.sendContent(htmlBuffer);
            htmlBuffer = "";
            yield(); 
        }
    }
    
    // Đóng thư mục
    closedir(dir);
    
    if (fileCount == 0) htmlBuffer += "<li><i>Thẻ nhớ trống hoặc file đang bị giấu trong thư mục con.</i></li>";
    htmlBuffer += "</ul>";
    
    if (htmlBuffer.length() > 0) server.sendContent(htmlBuffer);
    server.sendContent(""); 
}
// =======================================================================


void handleDelete() {
    if (!is_sd_controlled_by_wifi) return;
    if (server.hasArg("file")) {
        String filename = server.arg("file");
        if (SD.remove(filename)) { server.send(200, "text/plain", "Deleted"); return; }
    }
    server.send(500, "text/plain", "Delete Failed");
}

void handleFileUpload() {
    if (!is_sd_controlled_by_wifi) return;
    
    HTTPUpload& upload = server.upload();
    
    if (upload.status == UPLOAD_FILE_START) {
        String filename = upload.filename;
        
        // Giữ nguyên 100% tên file gốc, chỉ thêm dấu / nếu chưa có
        if (!filename.startsWith("/")) filename = "/" + filename;
        
        Serial.printf("\n[UPLOAD] Bat dau luu: %s\n", filename.c_str());
        
        SD.remove(filename); 
        uploadFile = SD.open(filename, FILE_WRITE);
    } 
    else if (upload.status == UPLOAD_FILE_WRITE) {
        if (uploadFile) {
            uploadFile.write(upload.buf, upload.currentSize);
            yield(); 
        }
    } 
    else if (upload.status == UPLOAD_FILE_END) {
        if (uploadFile) {
            uploadFile.close();
            Serial.printf("[UPLOAD] Hoan thanh: %u Bytes.\n", upload.totalSize);
        }
    }
}

void setup() {
    Serial.begin(115200);      
    Serial1.begin(115200, SERIAL_8N1, STM_RX_PIN, STM_TX_PIN); 
    delay(1000);
    
    Serial.println("\n--- KHOI DONG ESP32-C3 ---");


    is_sd_controlled_by_wifi = false;

    WiFi.disconnect(true, true); 
    WiFi.mode(WIFI_OFF);
    delay(500);
    
    WiFi.mode(WIFI_AP);
    WiFi.setTxPower(WIFI_POWER_8_5dBm); 
    WiFi.setSleep(false); 
    
    if (WiFi.softAP(ap_ssid, ap_password, 6, 0, 4)) {
        server.on("/", HTTP_GET, handleRoot);
        server.on("/status", HTTP_GET, handleStatus);
        server.on("/take", HTTP_GET, handleTakeControl);
        server.on("/release", HTTP_GET, handleReleaseControl);
        
        server.on("/list", HTTP_GET, handleFileList);
        
        server.on("/delete", HTTP_DELETE, handleDelete);
        
        server.on("/upload", HTTP_POST, []() { 
            server.send(200, "text/html", "<script>window.parent.uploadComplete();</script>"); 
        }, handleFileUpload);
        
        server.begin();
    }
}

void loop() {
    server.handleClient();
    if(Serial1.available()){
        Serial.write(Serial1.read());
    }
}
