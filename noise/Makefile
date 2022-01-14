
plot: data/504419/trddigits.root data/504419/trdtracklets.root
	root plot.C

dump: data/504419/trddigits.root data/504419/trdtracklets.root
	root dump.C

all: data/504419/trddigits.root

DATAFILES=data/504419/o2_ctf_run00504419_orbit0011066748_tf0000086459.root

download: $(DATAFILES)

data/504419/o2_ctf_run00504419_%:
	alien_cp /alice/data/2021/OCT_TRD/504419/raw/o2_ctf_run00504419_$*.root file:$@

data/%/trddigits.root: $(DATAFILES)
	cd $(dir $@) ; \
	o2-ctf-reader-workflow --onlyDet TRD --ctf-input $(notdir $<) | o2-trd-digittracklet-writer


