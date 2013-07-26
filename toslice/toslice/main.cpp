//
//  main.cpp
//  toslice
//
//  Created by wonhee jang on 13. 7. 25..
//  Copyright (c) 2013년 vanillabreeze. All rights reserved.
//

#include <iostream>
#include "libpsd.h"
#include <string.h>
#include <fstream>

int main(int argc, const char * argv[])
{
	psd_context *context_;
	psd_status status = psd_image_load(&context_, (psd_char *)(std::string(argv[1]) + ".psd").c_str());
	FILE* f = fopen((std::string(argv[1]) + ".uv").c_str(), "wb");
	
	unsigned int width = context_->width;
	unsigned int height = context_->height;
	fwrite(&width, sizeof(unsigned int), 1, f);
	fwrite(&height, sizeof(unsigned int), 1, f);
	
	for(int i = 0; i < context_->layer_count; i++) {
		psd_layer_record *record = &context_->layer_records[i];
		if(record->layer_type == psd_layer_type_normal) {
			
			unsigned long long length = strlen((char*)record->layer_name);
			fwrite(&length, sizeof(unsigned long long), 1, f);
			
			fwrite(&record->layer_name, length, 1, f);
			unsigned int pl = 4;
			fwrite(&pl, sizeof(unsigned int), 1, f);
			float l,t,r,b;
			l = (record->left - 2)/(float)context_->width;
			t = (record->top - 2)/(float)context_->height;
			r = (record->left + record->width + 2)/(float)context_->width;
			b = (record->top + record->height + 2)/(float)context_->height;
			fwrite(&l, sizeof(float), 1, f);
			fwrite(&t, sizeof(float), 1, f);
			fwrite(&r, sizeof(float), 1, f);
			fwrite(&t, sizeof(float), 1, f);
			fwrite(&l, sizeof(float), 1, f);
			fwrite(&b, sizeof(float), 1, f);
			fwrite(&r, sizeof(float), 1, f);
			fwrite(&b, sizeof(float), 1, f);
		}
	}
	
	fclose(f);
	psd_image_free(context_);
	
    return 0;
}

