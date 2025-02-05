from pathlib import Path

import librosa
from pydub.audio_segment import AudioSegment
from pydub.playback import play

from Aster import SOKYOEI_DATA_DIR

ROOT = Path(".").resolve().parent

# mp3
mp3 = AudioSegment.from_mp3(SOKYOEI_DATA_DIR / "Ahri/KDA_POP_STARS.mp3")
play(mp3)
print(mp3)

# mp3 = librosa.core.load(SOKYOEI_DATA_DIR / "Ahri/KDA_POP_STARS.mp3", sr=None)
# print(mp3)
