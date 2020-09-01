%ͨ�������������ֵ���Զ�������ά����

clc; clear; close all;

%��ȡ������Ϣ
[fin,message] = fopen('hull_free.dat', 'r');
if fin == -1
    disp (message);    %��ʾ������Ϣ
else
    disp(fin);
end
[data, count]=fscanf(fin,'%f');
fclose(fin);

xn = data(3);%���򻮷ֵ��������
yn = data(4);%���򻮷ֵ��������
grid_data = zeros(xn, yn, 3);

%%%%%%%����ϸ��%%%%%%%%
lineNum = int32(data(5));
line_data = zeros(lineNum, yn, 3);%����ϸ�������������
cc = 5;
for i = 1:lineNum
    %
    pointNum = data(cc+1);
    cc = cc + 1;
    %
    x = zeros(1, pointNum);
    y = zeros(1, pointNum);
    z = zeros(1, pointNum);  
    ss = zeros(1, pointNum); 
    for j = 1:pointNum
      x(j) = data(cc+1);
      y(j) = data(cc+2);
      z(j) = data(cc+3);
      cc = cc+3;
    end
    for j = 2:length(x)
      dis = ((x(j)-x(j-1))^2+(y(j)-y(j-1))^2+(z(j)-z(j-1))^2)^0.5;
      if(dis < 1e-5)
          dis = 1e-5;
      end
      ss(j) = ss(j-1) + dis;
    end
    plot3(x, y, z, 'r-.');
    hold on;
    ss1 = 0:ss(end)/(yn-1):ss(end);
    xx = spline(ss, x, ss1);
    yy = spline(ss, y, ss1);
    zz = spline(ss, z, ss1);
    line_data(i, :, :) = [xx' yy' zz'];%�洢
end

%%%%%%%����ϸ��%%%%%%%%%%%
for i = 1:yn
    x = line_data(:, i, 1)';
    y = line_data(:, i, 2)';
    z = line_data(:, i, 3)';
    ss = zeros(1, length(x));
    for j = 2:length(x)
      dis = ((x(j)-x(j-1))^2+(y(j)-y(j-1))^2+(z(j)-z(j-1))^2)^0.5;
      if(dis < 1e-5)
          dis = 1e-5;
      end
      ss(j) = ss(j-1) + dis;
    end

    hold on;
    ss1 = 0:ss(end)/(xn-1):ss(end);
    xx = spline(ss, x, ss1);
    yy = spline(ss, y, ss1);
    zz = spline(ss, z, ss1);
    grid_data(:, i, :) = [xx' yy' zz'];%�洢
    plot3(xx, yy, zz, 'b-.');
end

surf(grid_data(:,:,1), grid_data(:,:,2), grid_data(:,:,3));
axis equal;
%shading interp;


