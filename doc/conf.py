# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'libfabbri'
copyright = '2022, Lesleis Nagy'
author = 'Lesleis Nagy'
release = '1.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.mathjax',
    'sphinx.ext.viewcode',
    'sphinx.ext.imgmath',
    'sphinx.ext.todo',
    'sphinxcontrib.bibtex',
    'breathe',
]

latex_elements = {
    'preamble': r'''
        % Custom LaTeX preamble
        \usepackage{amsmath,amssymb,amsfonts}  % AMS math packages
        \usepackage{graphicx}                  % For including graphics
        \usepackage{geometry}                  % For custom page geometry
        \usepackage{bm}                        % package for bold math
        \usepackage{array}                     % For flexible table layout
        \usepackage{booktabs}                  % For cleaner tables
        
        % Default is 6pt; increase for more padding
        \setlength{\tabcolsep}{10pt}
        
        % Default is 1; increase for more vertical spacing
        \renewcommand{\arraystretch}{1.5}   
        
        % Custom commands
        \newcommand{\R}{\mathbb{R}}                             % Real numbers symbol
        \newcommand{\E}{\mathbb{E}}                             % Expectation symbol
        \newcommand{\vecrmin}{\ensuremath{\bm{r}^\mathrm{min}}}
        \newcommand{\vecrmid}{\ensuremath{\bm{r}^\mathrm{mid}}}
        \newcommand{\vecrmax}{\ensuremath{\bm{r}^\mathrm{max}}}
        \newcommand{\rmin}[1]{\ensuremath{r^\mathrm{min}_{#1}}}
        \newcommand{\rmid}[1]{\ensuremath{r^\mathrm{mid}_{#1}}}
        \newcommand{\rmax}[1]{\ensuremath{r^\mathrm{max}_{#1}}}
    ''',
    'figure_align': 'H',  # Align figures to 'H' (here)
}

bibtex_bibfiles = ['refs.bib']
bibtex_default_style = 'plain'
bibtex_reference_style = 'label'

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinxdoc'
html_static_path = ['_static']
numfig = True
numfig_format = {
    'table': 'Table %s',
    'figure': 'Fig. %s',
    'code-block': 'Listing %s',
}

import subprocess
subprocess.call("make clean", shell=True)
subprocess.call("doxygen Doxyfile", shell=True)
breathe_projects = { "libfabbri": "xml" }
breathe_default_project = "libfabbri"

