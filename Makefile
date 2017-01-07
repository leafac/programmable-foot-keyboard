.PHONY: documentation documentation/deploy documentation/clean clean

documentation: compiled-documentation/index.html

compiled-documentation/index.html: documentation/programmable-foot-keyboard.scrbl
	cd documentation && raco scribble --dest ../compiled-documentation/ --dest-name index -- programmable-foot-keyboard.scrbl

documentation/deploy: documentation
	rsync -av --delete compiled-documentation/ leafac.com:leafac.com/websites/software/programmable-foot-keyboard/

documentation/clean:
	rm -rf compiled-documentation

clean: documentation/clean
