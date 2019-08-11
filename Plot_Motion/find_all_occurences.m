function ret= find_all_occurences(a)
    p=table();
    [~, n]=size(a);
    p=a(1,1);
    for i=1:n
        [~, k]=size(p);
        flag=0;
        for j=1:k
            if(strcmp(table2cell(a(1,i)),table2cell(p(1,j)))==1)
                flag=1;
                break;
            end  
        end
        if(flag==0)
            p(1,k+1)=a(1,i);
        end 
    end
    ret=p;               
end
