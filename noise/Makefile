
help: ## Print this help text
	@perl -nle 'printf("  %-20s %s\n",$$1,$$2) if /^(\S+):.*##\s*(.*)/' $(MAKEFILE_LIST) | sort

PROCESSFILES = data/504419/trddigits.root data/504419/trdtracklets.root


plot: $(PROCESSFILES) ## Plotting
	root plot.C

dump: data/504419/trddigits.root data/504419/trdtracklets.root ## dump tracklets and 
	root dump.C

convert: $(PROCESSFILES) ## Convert CTF to tracklets/digits files




data/504419/trddigits.root data/504419/trdtracklets.root: \
	data/504419/o2_ctf_run00504419_orbit0000106748_tf0000000834.root



# data/grid/2021/OCT_TRD/504419/o2_ctf_run00504419_orbit0011066748_tf0000086459.root
# data/504419/o2_ctf_run00504419_orbit0000181756_tf0000001420.root


# download: $(DATAFILES)

data/grid/%/: 
	alien_cp /alice/data/$* file:$@
# alien_cp /alice/data/2021/OCT_TRD/504419/raw/o2_ctf_run00504419_$*.root file:$@

data/%/trddigits.root data/%/trdtracklets.root:
	cd $(dir $@) ; \
	o2-ctf-reader-workflow --onlyDet TRD --ctf-input $(notdir $<) | o2-trd-digittracklet-writer


