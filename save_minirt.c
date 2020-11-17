#include "minirt.h"

void
    bmp_header_2(int fd, int image_size)
{
    int bpp;
    int color;

    bpp = 24;
    write(fd, &bpp, 2);
    write(fd, "\0\0\0\0", 4);
    write(fd, &image_size, 4);
    color = 0;
    write(fd, &color, 4);
    write(fd, &color, 4);
    write(fd, &color, 4);
    write(fd, &color, 4);
}
void
    bmp_header(t_param *p_ptr, int fd)
{
    int file_size;
    int offset;
    int info_hsize;
    int planes;
    int extra_bytes;

    write(fd, "BM", 2);
    extra_bytes = (p_ptr->res_x % 4);
    offset = 54;
    file_size = (3 * p_ptr->res_x + extra_bytes) * p_ptr->res_y + offset;
    write(fd, &file_size, 4);
    write(fd, "\0\0\0\0", 4);
    write(fd, &offset, 4);
    info_hsize = 40;
    write(fd, &info_hsize, 4);
    write(fd, &(p_ptr->res_x), 4);
    write(fd, &(p_ptr->res_y), 4);
    planes = 1;
    write(fd, &planes, 2);
    bmp_header_2(fd, file_size - offset);
}

void
    save_minirt(t_param *p_ptr)
{
    p_ptr->fd_bmp = open("capture_rt.bmp", O_CREAT | O_WRONLY, 00700);
    bmp_header(p_ptr, p_ptr->fd_bmp);
}

// int main(void)
// {
//     t_param param;

//     param.res_x = 100;
//     param.res_y = 80;
//     save_minirt(&param);
// }