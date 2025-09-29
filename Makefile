all: iwd mod

iwd: 
	@./makeIWD.bat

mod: 
	@./makeMod.bat

.PHONY: all iwd mod
