def imfilter(arr,ftype):
    """
    Simple filtering of an image.
    Parameters
    ----------
    arr : ndarray
        The array of Image in which the filter is to be applied.
    ftype : str
        The filter that has to be applied. Legal values are:
        'blur', 'contour', 'detail', 'edge_enhance', 'edge_enhance_more',
        'emboss', 'find_edges', 'smooth', 'smooth_more', 'sharpen'.
    Returns
    -------
    imfilter : ndarray
        The array with filter applied.
    Raises
    ------
    ValueError
        *Unknown filter type.*  If the filter you are trying
        to apply is unsupported.
    """
    _tdict = {'blur':ImageFilter.BLUR,
              'contour':ImageFilter.CONTOUR,
              'detail':ImageFilter.DETAIL,
              'edge_enhance':ImageFilter.EDGE_ENHANCE,
              'edge_enhance_more':ImageFilter.EDGE_ENHANCE_MORE,
              'emboss':ImageFilter.EMBOSS,
              'find_edges':ImageFilter.FIND_EDGES,
              'smooth':ImageFilter.SMOOTH,
              'smooth_more':ImageFilter.SMOOTH_MORE,
              'sharpen':ImageFilter.SHARPEN
              }

    im = toimage(arr)
    if ftype not in _tdict:
        raise ValueError("Unknown filter type.")
    return fromimage(im.filter(_tdict[ftype]))