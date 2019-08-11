function f=ram(a)
f=table();
prev=a(1,1);
[~,n]=size(a);
k=1;
for i=1:n
    if(strcmp(table2cell(a(1,i)),table2cell(prev(1,1)))==1)
        por=cell(1,1);
        por(1,1)=cellstr(num2str(k));
        f(1,i)=cell2table(por);
    else
        prev=a(1,i);
        k=k+1;
        por=cell(1,1);
        por(1,1)=cellstr(num2str(k));
        f(1,i)=cell2table(por);
    end
end
