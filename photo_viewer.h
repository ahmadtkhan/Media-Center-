#ifndef ___PHOTO_VIEWER_H
#define ___PHOTO_VIEWER_H

//extern unsigned char ROSE_IMAGE_pixel_data[];
//extern unsigned char GIMP_IMAGE_RAMS_pixel_data[];
//extern unsigned char GIMP_IMAGE_JORDON_pixel_data[];

extern void photo_viewer();
extern void render_picture(int image_id);
extern void magnify_image(unsigned char *img_pointer);

#endif