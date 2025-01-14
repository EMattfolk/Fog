#!/usr/bin/python3
from os import listdir as ls
import os.path as path
from functools import reduce
from enum import Enum
from highlighter import highlight_code

def search(region, root):
    files_in_lists = [search(f, path.join(root, f)) for f in ls(root)
                                    if path.isdir(path.join(root, f))] +\
                     [[(region, path.join(root, f)) for f in ls(root)
                                    if path.isfile(path.join(root, f))]]
    files = reduce(lambda a, b: a + b, files_in_lists)
    return files

# Defines the sorting order for them
SECTION = 0
FUNC = 2
COMMENT = 3
END = 4


def find_comments(file_path):
    f = open(file_path)
    appending_to_comment = False
    comments = []
    current_type = None
    comment = ""
    for line in f:
        if not appending_to_comment:
            next_type = None
            if "//*" in line:
                next_type = FUNC
            elif "////" in line:
                next_type = COMMENT
            elif "//--" in line:
                next_type = SECTION
            elif "//--" in line or "////" in line:
                next_type = END
                line = ""

            if next_type is not None:
                appending_to_comment = True
                if current_type is not None:
                    comments.append((current_type, comment))
                if next_type is END:
                    current_type = None
                else:
                    current_type = next_type
                comment = ""

        elif appending_to_comment:
            if line.strip() == "":
                appending_to_comment = False
            else:
                comment += line
    if comment:
        comments.append((current_type, comment))
    return comments


all_files = search("core", "src/")
comments = dict()

for region, file_path in all_files:
    if not region in comments:
        comments[region] = []
    comments[region] += find_comments(file_path)

def tag(tag, content, html_class=""):
    html_class = " class='{}'".format(html_class) if html_class else ""
    return "<{}{}>{}</{}>".format(tag, html_class, content, tag)

def format_comment(comment):
    out = ""
    in_comment = False
    for line in comment.split("\n"): 
        if line.strip() == "": continue
        if not in_comment and line.startswith("//"):
            in_comment = True
            if out:
                out += "</p>"
            out += "<p class='ex comment'>"
        if in_comment and not line.startswith("//"):
            in_comment = False
            out += "</p>"
            out += "<p class='ex code'>"
        if in_comment:
            out += " " + line.replace("//", "").strip()
        else:
            indent = len(line) - len(line.lstrip())
            out += "<span indent=\"{}\"></span>"\
                    .format("#" * indent)
            out += highlight_code(line.replace("<", "&lt;").replace(">", "&gt;").lstrip())
            out += "<br>"
    return out.strip()

def format_desc(comment):
    return tag("p", comment.replace("//--", "").replace("//", "").strip(), "description")

with open("doc/doc.html", "w") as f:
    preamble = "\
<html>\
    <head>\
        <title>Fog - Documentation</title>\
        <meta charset=utf-8>\
        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
    </head>\
    <body>"
    f.write(preamble)
    for region in sorted(comments):
        f.write(tag("h2", region.capitalize(), "title"))
        for comment_type, comment in sorted(comments[region]):
            if not comment: continue
            # Formats the comments to a more suitable HTML format.
            if comment_type == SECTION:
                output = format_desc(comment)

            if comment_type == FUNC or comment_type == COMMENT:
                output = format_comment(comment)
                output = tag("div", output, "block")

            f.write(output)
    f.write("</body></html>")
    f.close()
