.PHONY: documentation documentation/deploy

project = programmable-foot-keyboard

documentation: documentation/index.html

documentation/index.html: documentation/$(project).scrbl
	cd documentation && raco scribble --dest-name index -- $(project).scrbl

documentation/deploy: documentation
	rsync -av --delete documentation/ leafac.com:leafac.com/websites/software/$(project)/
