if HAVE_DOXYGEN

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
pdf-local:
	cd latex; make pdf
clean-local:
	rm -rf $(top_srcdir)/docs/html $(top_srcdir)/docs/latex
endif