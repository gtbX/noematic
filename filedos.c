/* DOS is limited to 8.3 filenames;
 * Walk the path and truncate any file names over 8 chars to 6, adding ~1.
 * Also truncate extensions to 3 chars.
 * !This assumes there won't be any LFNs that truncate down to the same SFN! */
char* get_filename(char* path) {
    char* r = path, *w = path;
    int nlen = 0, elen = 0;
    int name = 1;
    while (*w = *r++) {
	if (*w == '\\' || *w == '/') {
	    if (*w == '/') *w = '\\';
	    name = 1;
	    nlen = 0;
	    elen = 0;
	} else if (name) {
	    nlen++;
	    if (*w == '.') {
		name = 0;
	    } else {
		if (nlen >= 9) {
		    if (nlen == 9) {
			w[-2] = '~';
			w[-1] = '1';
		    }
		    w--;
		}
	    }
	} else {
	    elen++;
	    if (elen > 3) {
		w--;
	    }
	}
	w++;
    }
    return path;
}
