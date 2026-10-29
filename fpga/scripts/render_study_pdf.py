"""Render Korean study Markdown to a searchable PDF with embedded fonts."""
from pathlib import Path
import sys
import re
from html import escape
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / '.tools/python'))
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib import colors
from reportlab.lib.styles import ParagraphStyle
from reportlab.lib.enums import TA_LEFT
from reportlab.lib.pagesizes import A4
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Preformatted

pdfmetrics.registerFont(TTFont('Malgun', 'C:/Windows/Fonts/malgun.ttf'))
pdfmetrics.registerFont(TTFont('MalgunBold', 'C:/Windows/Fonts/malgunbd.ttf'))
pdfmetrics.registerFontFamily('Malgun', normal='Malgun', bold='MalgunBold')
pdfmetrics.registerFont(TTFont('Code', 'C:/Windows/Fonts/consola.ttf'))
styles = {
    'body': ParagraphStyle('body', fontName='Malgun', fontSize=9.5, leading=16, spaceAfter=8, wordWrap='CJK'),
    'h1': ParagraphStyle('h1', fontName='MalgunBold', fontSize=23, leading=32, spaceAfter=18, wordWrap='CJK'),
    'h2': ParagraphStyle('h2', fontName='MalgunBold', fontSize=15, leading=23, spaceBefore=18, spaceAfter=10, keepWithNext=True, wordWrap='CJK'),
    'h3': ParagraphStyle('h3', fontName='MalgunBold', fontSize=11.5, leading=18, spaceBefore=12, spaceAfter=6, keepWithNext=True, wordWrap='CJK'),
    'code': ParagraphStyle('code', fontName='Code', fontSize=8, leading=11,
                           backColor=colors.HexColor('#f1f5f9'), borderPadding=7,
                           leftIndent=7, rightIndent=7, spaceBefore=4, spaceAfter=10),
}

def inline(s):
    s = escape(s)
    s = re.sub(r'\[([^\]]+)\]\(([^)]+)\)', r'\1', s)
    s = re.sub(r'`([^`]+)`', r'<font color="#24577d">\1</font>', s)
    return re.sub(r'\*\*([^*]+)\*\*', r'<b>\1</b>', s)

story = []
in_code = False
code_lines = []
for line in (ROOT / 'docs/FPGA_STUDY.md').read_text(encoding='utf-8').splitlines():
    if line.startswith('```'):
        if in_code:
            story.append(Preformatted('\n'.join(code_lines), styles['code']))
            code_lines = []
        in_code = not in_code
        continue
    if in_code:
        code_lines.append(line)
        continue
    if not line.strip(): continue
    kind = 'body'
    for prefix, value in [('### ', 'h3'), ('## ', 'h2'), ('# ', 'h1')]:
        if line.startswith(prefix):
            line, kind = line[len(prefix):], value
            break
    if line.startswith('- '): line = '• ' + line[2:]
    story.append(Paragraph(inline(line), styles[kind]))

def footer(canvas, doc):
    canvas.setFont('Malgun', 8)
    canvas.setFillColor(colors.HexColor('#64748b'))
    canvas.drawString(44, 28, 'FPGA 디지털 회로 설계 | 2026-10-26 | 학습 보고서')
    canvas.drawRightString(A4[0] - 44, 28, str(doc.page))

out = ROOT / 'docs/FPGA_STUDY.pdf'
SimpleDocTemplate(str(out), pagesize=A4, rightMargin=44, leftMargin=44, topMargin=42, bottomMargin=48,
                  title='FPGA 디지털 회로 설계 학습 보고서', author='FPGA Study Archive').build(story, onFirstPage=footer, onLaterPages=footer)
print(f'PDF generated: {out} ({out.stat().st_size:,} bytes)')
