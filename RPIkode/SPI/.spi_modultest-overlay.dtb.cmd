cmd_/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb := mkdir -p /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/ ; arm-poky-linux-gnueabi-gcc -E -Wp,-MD,/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.dts.tmp /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dts ; ./scripts/dtc/dtc -O dtb -o /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb -b 0 -i/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/ -i./scripts/dtc/include-prefixes -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-gpios_property -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-graph_port -Wno-simple_bus_reg -Wno-unique_unit_address -Wno-pci_device_reg  -d /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.d.dtc.tmp /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.dts.tmp ; cat /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.d.pre.tmp /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.d.dtc.tmp > /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/.spi_modultest-overlay.dtb.d

source_/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb := /mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dts

deps_/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb := \

/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb: $(deps_/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb)

$(deps_/mnt/c/Users/dryos/Documents/GitHub/E5PRJ3/RPIkode/SPI/spi_modultest-overlay.dtb):
