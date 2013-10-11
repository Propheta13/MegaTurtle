#ifndef TAIL_H
#define TAIL_H

#ifdef __cplusplus
namespace Tail {
#endif //__cplusplus

    typedef enum
    {
        RawStone = 0x0000
    } tailtype_t;

    typedef struct
    {
        union
        {
            char coords[4];
            struct
            {
                char z1, z2, z3, z4;
            };
        };

        unsigned short type;
        unsigned short attributes;
    } tail_t;

    typedef struct
    {
        unsigned int tail_count;
        unsigned int tail_h;
        unsigned int tail_w;
        unsigned int map_resolution_h;
        unsigned int map_resolution_w;
        unsigned int tail_resolution;
    } tailmap_header_t;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // TAIL_H
