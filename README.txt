Game cỗ xe bắn quái
Được viết bằng ngôn ngữ C++ kết hợp với SDL2 
-Nội dung game : Một cỗ xe có thể di chuyển được trên map của game.
Nhiệm vụ của nó là vượt qua các chướng ngại vật và tiêu diệt các con quái bằng đạn bắn 
(Để xe di chuyển sang trái ấn mũi tên trái, sang bên phải thì ấn mũi tên phải, để xe nhảy lên ấn chuột trái, tạo đạn bắn ấn chuột phải) 
Các lớp đối tượng trong game: 
-Lớp chứa các đối tượng chung, hàm khởi tạo ban đầu trong game(func) 
-Lớp đối tượng tổng, các lớp sau kế thừa từ đối tượng này(Baseobject) 
-Lớp nhân vật chính(cỗ xe, Mainobject) 
-Lớp địch (Threatobject) 
-Lớp đạn (Bulletobject) 
-Lớp load text(text) 
-Lớp chỉ số ips thời gian(imptimer) 
-Hàm main chính(gngnn