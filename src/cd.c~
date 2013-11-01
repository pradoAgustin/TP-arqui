#include "../include/defs.h"
#define BIT31 0x80000000 
/* Siempre en 1 */
#define BITS30A24 0x7F000000
/* Siempre en 0 */
#define BITS23A16 0x00FF0000
/* Bus Number */
#define BITS15A11 0x0000F800
/* Device Number */
#define BITS10A8 0x00000700
/* Function Number */
#define BITS7A0 0x000000FF
/*Register Number*/

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

//supuestamente el controlador del cd esta en un bus pci, primero tenes que leer dnd esta el ata controller, dsp tendrias que ver la funcionalidad de la atapi en si.
//como leer el bus pci(cada registro) para poder encontrar el dispositivo adecuada


//http://www.pcidatabase.com/search.php?device_search_str=ctrlr
//device id, chip description, vendor id, vendor name
	//{ 0x112E, 0x0000, "", "EIDE/hdd and IDE/cd-rom Ctrlr" } ,//vendor id:4398d device id:0d
	//{ 0x112E, 0x000B, "", "EIDE/hdd and IDE/cd-rom Ctrlr" } ,//vendor id:4398d device id:11d



//0x0001	EIDE/ATAPI super adapter	0x1141	Crest Microsystem Inc



void getPci();
//http://wiki.osdev.org/PCI#PCI_Device_Structure accedemos a los buses y dispositivos por fuerza bruta

    typedef struct {
	unsigned short	vendorId ;
	unsigned short	deviceId ;
	char * vendor;
	char * device;
} PCI_TABLE;

PCI_TABLE pciTable[] = {
    /*Fuente: http://pci-ids.ucw.cz/v2.2/pci.ids */
    /* Para Dell Inspiron 15R */
	{0x8086, 0x0154, "Intel Corporation", "3rd Gen Core processor DRAM Controller"},
    {0x8086, 0x0156, "Intel Corporation", "3rd Gen Core processor Graphics Controller"},
    {0x8086, 0x1e31, "Intel Corporation", "7 Series/C210 Series Chipset Family USB xHCI Host Controller"},
    {0x8086, 0x1e3a, "Intel Corporation", "7 Series/C210 Series Chipset Family MEI Controller #1"},
    {0x8086, 0x1e2d, "Intel Corporation", "7 Series/C210 Series Chipset Family USB Enhanced Host Controller #2"},
    {0x8086, 0x1e20, "Intel Corporation", "7 Series/C210 Series Chipset Family High Definition Audio Controller"},
    {0x8086, 0x1e10, "Intel Corporation", "7 Series/C210 Series Chipset Family PCI Express Root Port 1"},
    {0x8086, 0x1e12, "Intel Corporation", "7 Series/C210 Series Chipset Family PCI Express Root Port 2"},
    {0x8086, 0x1e26, "Intel Corporation", "7 Series/C210 Series Chipset Family USB Enhanced Host Controller #1"},
    {0x8086, 0x1e57, "Intel Corporation", "HM77 Express Chipset LPC Controller"},
    {0x8086, 0x1e03, "Intel Corporation", "7 Series Chipset Family 6-port SATA Controller [AHCI mode]"},
    {0x8086, 0x1e22, "Intel Corporation", "7 Series/C210 Series Chipset Family SMBus Controller"},
    {0x10ec, 0x8136, "Realtek Semiconductor Co., Ltd.", "RTL8101E/RTL8102E PCI Express Fast Ethernet controller"},
    /* Para VirtualBox */
    {0x8086, 0x1237, "Intel Corporation", "440FX - 82441FX PMC [Natoma]"},
    {0x8086, 0x7000, "Intel Corporation", "82371SB PIIX3 ISA [Natoma/Triton II]"},
    {0x8086, 0x7111, "Intel Corporation", "82371AB/EB/MB PIIX4 IDE"},
    {0x80ee, 0xbeef, "InnoTek Systemberatung GmbH", "VirtualBox Graphics Adapter"},
    {0x80ee, 0xcafe, "InnoTek Systemberatung GmbH", "VirtualBox Guest Service"},
    {0x8086, 0x100e, "Intel Corporation", "82540EM Gigabit Ethernet Controller"},
    {0x8086, 0x2415, "Intel Corporation", "82801AA AC'97 Audio Controller"},
    {0x106b, 0x003f, "Apple Inc.", "KeyLargo/Intrepid USB"},    
    {0x8086, 0x7113, "Intel Corporation", "82371AB/EB/MB PIIX4 ACPI"},  
    {0x8086, 0x2829, "Intel Corporation", "82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode]"}      
};
    
int dimPciTable = sizeof(pciTable)/sizeof(PCI_TABLE);

void printPci(unsigned short vendorId, unsigned short deviceId) {
    int i;
    if ( vendorId == 0xFFFF )
        return ;
    for ( i = 0; i < dimPciTable; i++ ) {
        if (pciTable[i].vendorId == vendorId && pciTable[i].deviceId == deviceId) {
            printf("%s - %s\n", pciTable[i].vendor, pciTable[i].device);
            return ;
        }
    }
}
        
void getPci(void) {
    unsigned short vendorId, deviceId;
    int bus, device, reg = 0, mask, data, fun = 0, prints = 0;
	mask = 0xFFFF;
	for ( bus = 0; bus < 256; bus++ ) 
		for ( device = 0; device < 32; device++ ) {
            mask = BIT31 | BITS30A24 | ((bus << 16) & BITS23A16) |
                   ((device << 11) & BITS15A11) | 
                   (fun & BITS10A8) | (reg & BITS7A0);
            outport32(CONFIG_ADDRESS, mask);
            data = inport32(CONFIG_DATA);
            if ( data != 0xFFFFFFFF && data != 0x00000000 ) {
                vendorId = data & 0x0000FFFF;
                deviceId = (data & 0xFFFF0000) >> 16;
                printPci(vendorId,deviceId);
                prints++;
                if(prints % 10 == 0) {
                    printf("Presione enter para continuar.\n");
                    while(getchar()!= '\n');
                }
            }
        }
}
