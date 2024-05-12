
#ifndef __GDT_H
#define __GDT_H

#include "types.h"

    class GlobalDescriptorTable{
        public:
            class SegmentDescriptor{
                private:
                    uint16_t limit_lo; //Various allocated memory segments
                    uint16_t base_lo;
                    uint8_t base_hi;
                    uint8_t type;
                    uint8_t flags_limit_hi;
                    uint8_t base_vhi;
                public:
                    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type); //Constructor
                    uint32_t Base();
                    uint32_t Limit();

            } __attribute__((packed)); //needs to be "byte perfect" stops compiler from doing weird stuff

            SegmentDescriptor nullSegmentSelector; //emptySegment
            SegmentDescriptor unusedSegmentSelector; //unusedSegment
            SegmentDescriptor codeSegmentSelector; //code
            SegmentDescriptor dataSegmentSelector; //you get the jist
        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            uint16_t CodeSegmentSelector();
            uint16_t DataSegmentSelector();

    }; //why this here... the colon?






#endif
