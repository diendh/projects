//
//  ReadFileTXT.cpp
//  CoTuong3
//
//  Created by Đỗ Hữu Điển on 12/7/13.
//
//

#include "ReadFileTXT.h"

ReadFileTXT::ReadFileTXT(string path){
    
    FILE *fp = fopen(path.c_str(), "r");
    char buf[50] = {0};
    
    if (! fp)
    {
        printf("can not open file %s", path.c_str());
        return;
    }
    
    fgets(buf, 50, fp);
    printf("read content %s", buf);
    
    fclose(fp);
}

ReadFileTXT::~ReadFileTXT(){
    
}