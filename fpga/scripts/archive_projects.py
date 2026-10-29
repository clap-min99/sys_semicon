"""Copy authored Vivado inputs, retaining layout and recording provenance."""
from pathlib import Path
import csv
import hashlib
import shutil
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
SOURCE = Path('D:/project/fpga/ai2')
DEST = ROOT / 'projects'
rows, summaries, issues = [], [], []

def copy_file(src, dst, reason='original'):
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src, dst)
    digest = hashlib.sha256(src.read_bytes()).hexdigest()
    assert digest == hashlib.sha256(dst.read_bytes()).hexdigest()
    rows.append([str(src), dst.relative_to(ROOT).as_posix(), src.stat().st_size, digest, reason])

for project in sorted(SOURCE.iterdir()):
    if not project.is_dir():
        continue
    files = []
    for src in sorted(project.rglob('*')):
        if not src.is_file():
            continue
        rel = src.relative_to(project)
        in_sources = any(p.endswith('.srcs') for p in rel.parts)
        keep = (in_sources and src.suffix.lower() in {'.v', '.sv', '.vh', '.xdc', '.mem', '.coe', '.hex', '.xci', '.bd'})
        keep |= len(rel.parts) == 1 and src.suffix.lower() in {'.xpr', '.wcfg', '.md'}
        keep |= rel.parts[0] == 'tests' and src.suffix.lower() in {'.v', '.sv', '.tcl', '.ps1', '.md'}
        if keep:
            copy_file(src, DEST / project.name / rel)
            files.append(rel)
    xprs = list((DEST / project.name).glob('*.xpr'))
    design_top = sim_top = '-'
    for xpr in xprs:
        tree = ET.parse(xpr)
        for fs in tree.findall('.//FileSet'):
            for option in fs.findall('./Config/Option'):
                if option.get('Name') == 'TopModule':
                    if fs.get('Name') == 'sources_1': design_top = option.get('Val')
                    if fs.get('Name') == 'sim_1': sim_top = option.get('Val')
        content = xpr.read_text(encoding='utf-8')
        for node in tree.findall('.//File'):
            ref = node.get('Path', '')
            resolved = ref.replace('$PSRCDIR', str(project / (xpr.stem + '.srcs'))).replace('$PPRDIR', str(project))
            src_ref = Path(resolved)
            if '$' in resolved: continue
            if not src_ref.is_file():
                issues.append(f'{project.name}: 원본 참조 파일 없음: {ref}')
            elif not src_ref.resolve().is_relative_to(project.resolve()):
                dst = xpr.parent / 'external' / src_ref.name
                copy_file(src_ref, dst, 'external dependency; copied xpr reference localized')
                content = content.replace(ref, '$PPRDIR/external/' + src_ref.name)
        xpr.write_text(content, encoding='utf-8')
    summaries.append((project.name, files, design_top, sim_top))

docs = ROOT / 'docs'
docs.mkdir(exist_ok=True)
with (docs / 'COPY_MANIFEST.csv').open('w', encoding='utf-8-sig', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['original_path', 'copied_path', 'bytes', 'original_sha256', 'note'])
    writer.writerows(rows)
lines = ['# 프로젝트별 코드 목록', '', '원본: `D:\\project\\fpga\\ai2` / 정리일: 2026-10-26', '',
         '경로 구조와 코드 바이트를 보존했다. 외부 의존 파일은 external에 복사하고 복사본 XPR 참조만 조정했다.',
         'XPR은 텍스트 저장 과정에서 줄바꿈이 바뀔 수 있으므로 매니페스트의 XPR 해시는 원본 기준이다.', '',
         '| 프로젝트 | 설계 Top | 시뮬레이션 Top | 복사 파일 수 |', '|---|---|---|---|']
for name, files, top, tb in summaries:
    lines.append(f'| {name} | {top} | {tb} | {len(files)} |')
for name, files, top, tb in summaries:
    lines += ['', f'## {name}', '', f'설계 Top: `{top}` / 시뮬레이션 Top: `{tb}`', '']
    if not files: lines.append('복사 대상 소스가 없는 빈 프로젝트 폴더. 학습 구현으로 집계하지 않는다.')
    for rel in files:
        url = '../projects/' + name + '/' + rel.as_posix()
        lines.append(f'- [{rel.as_posix()}]({url})')
lines += ['', '## 원본 참조 누락', ''] + ['- ' + s for s in issues]
(docs / 'CODE_INDEX.md').write_text('\n'.join(lines) + '\n', encoding='utf-8')
print(f'Copied {len(rows)} files in {len(summaries)} project folders; missing references: {len(issues)}')
for s in issues: print(s)
