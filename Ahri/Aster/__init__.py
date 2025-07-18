import os
from pathlib import Path

ASTER_ROOT = Path(__file__).resolve().parent.parent.parent

sokyoei_data_dir = os.environ.get("SOKYOEI_DATA_DIR")
if sokyoei_data_dir:
    SOKYOEI_DATA_DIR = Path(sokyoei_data_dir)
else:
    raise RuntimeError("Please install https://github.com/Sokyoei/data")
