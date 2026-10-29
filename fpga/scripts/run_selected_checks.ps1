$ErrorActionPreference = 'Stop'
$archiveRoot = Split-Path $PSScriptRoot -Parent
$vivadoBin = 'C:\Xilinx\Vivado\2020.2\bin'
$cases = @(
    @{ Name = 'pwm_motor'; Src = 'pwm_motor.srcs'; Bench = 'tests\tb_motor.v'; Top = 'tb_motor' },
    @{ Name = 'mealy_fsm'; Src = 'mealy_fsm.srcs'; Bench = 'mealy_fsm.srcs\sim_1\new\tb_fsm_101_compare.v'; Top = 'tb_fsm_101_compare' }
)
foreach ($case in $cases) {
    $projectDir = Join-Path $archiveRoot ('projects\' + $case.Name)
    $runDir = Join-Path $archiveRoot ('.tools\validation\' + $case.Name)
    New-Item -ItemType Directory -Path $runDir -Force | Out-Null
    Push-Location $runDir
    try {
        $rtlFiles = @(Get-ChildItem (Join-Path $projectDir ($case.Src + '\sources_1')) -Recurse -Filter *.v | ForEach-Object FullName)
        & (Join-Path $vivadoBin 'xvlog.bat') --work xil_defaultlib @rtlFiles (Join-Path $projectDir $case.Bench)
        if ($LASTEXITCODE -ne 0) { throw 'xvlog failed' }
        & (Join-Path $vivadoBin 'xelab.bat') ('xil_defaultlib.' + $case.Top) -s archive_check
        if ($LASTEXITCODE -ne 0) { throw 'xelab failed' }
        & (Join-Path $vivadoBin 'xsim.bat') archive_check -runall
        if ($LASTEXITCODE -ne 0) { throw 'xsim failed' }
        $simLog = Get-Content xsim.log -Raw
        if ($simLog -notmatch 'PASS:' -or $simLog -match 'FAIL:') { throw 'Missing PASS or test reported FAIL' }
    } finally {
        Pop-Location
    }
}
