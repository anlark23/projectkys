
#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

    class InterruptManager{

    protected:

        struct GateDescriptor{
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;


        } __attribute__((packed)); //has to be "byte perfect"

        static GateDescriptor interruptDescriptorTable[256];

        struct InterruptDescriptorTablePointer{

            uint16_t size;
            uint32_t base;

        } __attribute__((packed));

        static void SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentSelectorOffset,
            void (*handler)(),
            uint8_t DescriptorPrivilegeLevel,
            uint8_t DescriptorType
        );

        Port8BitSlow picMasterCommand;
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveCommand;
        Port8BitSlow picSlaveData;



    public:

        InterruptManager(GlobalDescriptorTable* gdt);
        ~InterruptManager();

        void Activate();

        InterruptManager();

        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00(); //interrupt timer
        static void HandleInterruptRequest0x01(); //keyboard interrupts

    };


#endif
