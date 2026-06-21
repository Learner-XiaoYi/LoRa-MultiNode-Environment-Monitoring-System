filename = 'data.log';  
fid = fopen(filename, 'r');
if fid == -1
    error('文件打开失败：请检查文件路径或权限');
end
data = fscanf(fid, '%f');  
fclose(fid); 

% 数据可视化
figure; 
plot(data, 'b-o', 'LineWidth', 1.5);
xlabel('数据索引');
ylabel('测量值');
title('');
grid on;
set(gca, 'FontSize', 12);