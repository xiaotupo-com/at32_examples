from idlelib.outwin import file_line_pats
from pathlib import Path
import os
import subprocess
from itertools import chain
from typing import List, Iterable

def multi_glob(parent: Path, pattern_list: List[str], *, recursive=False) -> Iterable[Path]:
    if not recursive:
        func_glob = lambda s: parent.glob(s)
    else:
        func_glob = lambda s: s.glob(pattern_list)
    return chain(*(map(func_glob, pattern_list)))

here = os.path.dirname(__file__)
here = Path(here)

file_list = multi_glob(here, ['*.[ch]', '*.[ch]pp', '*[ch]xx'], recursive=True)

file_path_list = map(lambda f: str(f.relative_to(here)), file_list)

