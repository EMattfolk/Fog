TYPE_COLOR = "#f80"
TYPE_STRINGS = {
    "static", "void", "Vec2", "Vec3", "Vec4", "f32", "LogicID",
    "Callback", "At", "const", "bool", "int", "Function", "struct",
    "real", "s8", "s16", "s32", "s64", "u8", "u16", "u32", "u64",
    "AssetID", "Mapping", "InputCode", "Player", "Name"
}

MACRO_COLOR = "#0cc"
MACRO_STRINGS = {
    "LOG_MSG", "CLAMP", "LERP", "ABS", "ABS_MAX", "MAX", "SIGN",
    "SIGN_NO_ZERO", "ABS_MIN", "MIN", "IN_RANGE", "SQ", "MOD"
}

NUMBER_COLOR = "#c8c"

SPLIT_SEPS = set(" ,;()\n")

def highlight_code(line):
    """ Adds orange color to words marked to be highlighted """
    def highlight(word):
        if word in TYPE_STRINGS:
            return color_html(word, TYPE_COLOR)
        if word in MACRO_STRINGS:
            return color_html(word, MACRO_COLOR)
        if is_number(word):
            return color_html(word, NUMBER_COLOR)
        return word


    return "".join([highlight(w) + s for w, s in zip(*split_all(line, SPLIT_SEPS))])


def color_html(string, color):
    """ Wrap a string in a span with color specified as style. """
    return '<span style="color: {}">{}</span>'.format(color, string)


def split_all(string, sep):
    """
    Split a string at all characters in sep.
    Return two lists:
        words - Everything not including characters in sep
        splits - Everything including characters in sep

    Example:
        assert split_all("[1, 2]", " ,") == (["[1", "2]"], [", ", ""])

    The following is always true:
        len(words) == len(splits)
        len(words) > 0
        string == "".join([w + s for w, s in zip(*split_all(string, sep))])

    :param string str: String to split
    :param sep str: Characters where string should be split
    """
    words, splits = [], []
    word, split = "", ""
    i = 0
    while i < len(string):
        if string[i] in sep:
            words.append(word)
            word = ""
            while i < len(string) and string[i] in sep:
                split += string[i]
                i += 1
            splits.append(split)
            split = ""
            if i == len(string): break
        word += string[i]
        i += 1

    if word or not words:
        words.append(word)
        splits.append("")

    return words, splits


def is_number(string):
    """ Return whether or not a string is a number """
    return string.lstrip("-").replace(".", "", 1).isdigit()
