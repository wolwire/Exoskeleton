clear all;
clc;
a=readtable('drinktea_s2_25m_002.csv');
[m,n]=size(a);
workp=table();
i=1;
a(1,:)=ram(a(1,:));
for j=1:n
    if(strcmp(table2cell(a(2,j)),'Position')==1)
            workp(:,i)=a(:,j);
            i=i+1;
    end
end

workp2=table2array(workp(4:n,:));
[m,n]=size(workp2);
SkeletonConnectionMap=[
                      [39 40];%legl
                      [40 41] ;
                      [41 45];
                      [42 43];%legr
                      [43 44];
                      [44 46];
                      [1 39];%hip
                      [1 42];
                      [1 6];%abdomen
                      [1 7];%back
                      [7 8];
                      [2 3];%waist
                      [2 4];
                      [4 5];
                      [5 3];
                      [10 11];%chest
                      [11 9];
                      [9 10];
                      [9 2];
                      [9 3];
                      [10 4];
                      [11 5];
                      [12 13];%head
                      [13 14];
                      [14 15];
                      [17 18];%shoulder right
                      [18 19];
                      [19 17];
                      [19 20];
                      [18 20];
                      [17 20];
                      [21 20];
                      [20 23];
                      [20 21];
                      [20 22];
                      [23 20];
                      [21 22];
                      [21 23];
                      [22 23];
                      [23 25];
                      [21 24];
                      [22 26];
                      [24 25];
                      [25 26];
                      [26 27];
                      [28 29];%shoulder left
                      [29 30];
                      [30 28];
                      [30 31];
                      [31 29];
                      [31 28];
                      [31 30];
                      [31 32];
                      [31 33];
                      [31 34];
                      [34 32];
                      [32 33];
                      [32 36];
                      [34 37];
                      [33 35];
                      [35 36];
                      [36 37];
                      [37 38]];
[fi,~]=size(SkeletonConnectionMap);
label=cellstr(num2str([1:n/3]'));
view(3);
  writerObj = VideoWriter('myVideo1.avi');
  writerObj.FrameRate = 10;
   open(writerObj);
   p=1;
for i=1:3:m  
   SkeletalJoints=zeros(n/3,3);
   SkeletalJoints(1,1:3)=str2double(workp2(i,1:3)); 
    for j=4:3:n-2 
       SkeletalJoints((j+2)/3,1:3)=str2double(workp2(i,j:j+2));
    end
    hold on
    for k=1:fi
        plot3([SkeletalJoints(SkeletonConnectionMap(k,1),1),SkeletalJoints(SkeletonConnectionMap(k,2),1)],[SkeletalJoints(SkeletonConnectionMap(k,1),3),SkeletalJoints(SkeletonConnectionMap(k,2),3)],[SkeletalJoints(SkeletonConnectionMap(k,1),2),SkeletalJoints(SkeletonConnectionMap(k,2),2)],'color',[1-(i/m) 1-(i/m) 1-(i/m)]);
        %plot3(SkeletalJoints(k,1),SkeletalJoints(k,3),SkeletalJoints(k,2),'o'););
%         text([SkeletalJoints(SkeletonConnectionMap(k,1),1),SkeletalJoints(SkeletonConnectionMap(k,2),1)],[SkeletalJoints(SkeletonConnectionMap(k,1),3),SkeletalJoints(SkeletonConnectionMap(k,2),3)],[SkeletalJoints(SkeletonConnectionMap(k,1),2),SkeletalJoints(SkeletonConnectionMap(k,2),2)],label(k));
%          text(SkeletalJoints(k+20,1),SkeletalJoints(k+20,3),SkeletalJoints(k+20,2),label(k+20));
        xlim([-1 1]);
        ylim([-.5 .5]);
         zlim([0 2]);
      
    end
%      for k=1:46
%         text(SkeletalJoints(k,1),SkeletalJoints(k,3),SkeletalJoints(k,2),label(k));
%      end
      p=p+1;
    drawnow;
    writeVideo(writerObj, getframe(gcf));
%     if(p==5)
%         cla;
%         p=1;
%     end
%     pause(.001);
end
close(writerObj);
hold off;

            
           
                
        
        

