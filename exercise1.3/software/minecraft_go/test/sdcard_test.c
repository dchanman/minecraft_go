#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>

static int sdcard_test_write();

int sdcard_test_open(void)
{
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;

	printf("Opening SDCard\n");
	if((device_reference = alt_up_sd_card_open_dev("/dev/altera_up_sd_card_avalon_interface_0")) == NULL)
	{
		printf("SDCard Open FAILED\n");
		return 0 ;
	}
	else
		printf("SDCard Open PASSED\n");


	if (device_reference != NULL ) {
		while(1) {
			if ((connected == 0) && (alt_up_sd_card_is_Present())){
				printf("Card connected.\n");
				if (alt_up_sd_card_is_FAT16()) {
					printf("FAT16 file system detected.\n");
					sdcard_test_write();
				}
				else {
					printf("Unknown file system.\n");
				}
				connected = 1;
			} else if((connected == 1) && (alt_up_sd_card_is_Present() == false)){
				printf("Card disconnected.\n");
				connected =0;
			}
		}
	}
	else
		printf("Can't open device\n");

	return 0;
}

static int sdcard_test_write() {
	int i;
	short int myFileHandle;
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		if ((myFileHandle = alt_up_sd_card_fopen("test.txt", true)) != -1) {
			printf("File Opened\n");
			for (i = 0; i < 1024; i++) {
				if (alt_up_sd_card_write(myFileHandle, 'A') == false) {
					printf("Error writing to file...\n");
					return 0;
				}
			}
			printf("Done!!!\n");
			alt_up_sd_card_fclose(myFileHandle);
		} else
			printf("File NOT Opened\n");
	}

	return 0;
}
