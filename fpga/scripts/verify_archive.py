"""Check copied inputs and searchable Korean PDF; requires pypdf for PDF checks."""
from pathlib import Path
import csv
import hashlib
import sys
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / '.tools/python'))
from pypdf import PdfReader
rows = list(csv.DictReader((ROOT / 'docs/COPY_MANIFEST.csv').open(encoding='utf-8-sig')))
checked = 0
for row in rows:
    target = ROOT / row['copied_path']
    assert target.is_file(), target
    if target.suffix == '.xpr':
        continue  # XML text was resaved and one external reference localized.
    assert hashlib.sha256(target.read_bytes()).hexdigest() == row['original_sha256'], target
    checked += 1
reader = PdfReader(ROOT / 'docs/FPGA_STUDY.pdf')
texts = [page.extract_text() for page in reader.pages]
text = '\n'.join(texts)
for keyword in ['FPGA 디지털', '디바운', 'stopwatch', 'pwm_motor', '저장소 구성']:
    assert keyword in text, keyword
assert all(t.strip() for t in texts)
markdown = (ROOT / 'docs/FPGA_STUDY.md').read_text(encoding='utf-8')
if '## 9. 주요 코드 및 동작 해설' in markdown:
    assert markdown.count('```verilog') == 12
    for code in ['assign led[0]', 'r_FF2 <= r_FF1;', 'assign btn_pulse',
                 'TICK_COUNT', 'r_pwm_counter < r_duty_cycle', 'task send_data']:
        assert code in text, f'PDF missing code: {code}'
print(f'Files: {len(rows)}; byte-identical non-XPR inputs: {checked}; PDF: {len(reader.pages)} nonblank pages, Korean text extraction PASS')
