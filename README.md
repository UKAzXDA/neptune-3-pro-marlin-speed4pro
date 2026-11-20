# Neptune 3 Pro — Marlin com perfil de alta velocidade

Firmware comunitário não oficial para a Elegoo Neptune 3 Pro, baseado no Marlin 2.1.1 fornecido no pacote deste projeto. O alvo de compilação é `MKS_E3_V2` (STM32F401RC / placa MKS Robin E3 V2).

## Downloads

Baixe `ZNP_ROBIN_NANO.bin` nos **Assets** do release mais recente. O arquivo também está na raiz deste repositório.

## Resultado

Qualidade de impressão e velocidade comparáveis à velocidade padrão de uma Neptune 4 Pro. Esse é um relato de uso, não um benchmark independente nem uma garantia de resultado em outras impressoras, materiais ou configurações.

A compatibilidade com uma versão recente da tela LCD Elegoo. O modelo e a versão exata da tela vareia; portanto, a compatibilidade com outras revisões não é garantida.

## Usar perfis e G-code do Cura

Para usar o desempenho deste firmware, faça reset de fabrica no painel, e com versão recente do Cura Elegoo:
Use as configurações do perfil da Neptune 4 Pro e coloque G-code de início e fim da Neptune 3 pro.

### G-code de início

```gcode
;;===== date: 20240520 =====================
M400 ; wait for buffer to clear
;[printer_model]
;initial_filament:{filament_type[initial_extruder]}
;curr_bed_type={curr_bed_type}
M220 S100 ;Set the feed speed to 100%
M221 S100 ;Set the flow rate to 100%
M104 S140
M190 S[bed_temperature_initial_layer_single]
G90
G28 ;home
;G29 ; run abl mesh
M420 S1 ; load mesh
G1 Z10 F300
G1 X{print_bed_max[0]*0.5-50} Y0.5 F6000
G1 Z0.4 F300
M109 S[nozzle_temperature_initial_layer]
G92 E0 ;Reset Extruder
G1 X{print_bed_max[0]*0.5+50} E30 F400 ;Draw the first line
G1 Z0.6 F120.0 ;Move to side a little
G1 X{print_bed_max[0]*0.5+47} F3000
G92 E0 ;Reset Extruder
;LAYER_COUNT:[total_layer_count]
;LAYER:0
```

### G-code de fim

```gcode
;PRINT_END
G90 ;Absolute positionning
M83 ; extruder relative mode
G1 X10 Y{print_bed_max[1]*0.8} Z{min(max_layer_z+50, printable_height)} E-5 F{travel_speed*60} ; Move print head up
M106 S0 ;Turn-off fan
M104 S0 ;Turn-off hotend
M140 S0 ;Turn-off bed
M84 X Y E ;Disable all steppers but Z
```

Use valores de velocidade e fluxo conservadores no primeiro teste. Velocidade alta, fluxo excessivo ou um G-code incompatível com a revisão da máquina podem causar perda de passos, obstruções, superaquecimento ou danos mecânicos.

## Alterações de configuração

As alterações estão em `Firmware/Mainboard/Marlin-2.1.1_TJC_029/Marlin-2.1.1_TJC_029/Marlin/Configuration.h` e `Configuration_adv.h`:

| Parâmetro | Valor |
| --- | --- |
| Passos por unidade (X, Y, Z, E) | `{80, 80, 400, 415}` |
| Feedrate máximo (X, Y, Z, E) | `{500, 500, 20, 45}` mm/s |
| Aceleração máxima (X, Y, Z, E) | `{5000, 5000, 100, 3000}` mm/s² |
| Aceleração padrão | `4000` mm/s² |
| Aceleração de retração | `3000` mm/s² |
| Aceleração de deslocamento | `5000` mm/s² |
| Limite de temperatura do hotend | `315` °C |
| Limite de temperatura da mesa | `120` °C |
| Junction Deviation | `0.04` mm; Classic Jerk desativado |
| Linear Advance | Ativado, `LIN_ADVANCE_K = 0.00` |
| StealthChop | Desativado em X/Y; ativado em Z/E |
| Adaptive Step Smoothing | Ativado |

O valor K do Linear Advance começa em zero; ajuste-o no fatiador/G-code conforme o conjunto extrusor-filamento e calibre antes de depender dele em uma impressão.

**Input Shaping não está habilitado.** A versão Marlin 2.1.1 deste pacote não contém a implementação/opções `INPUT_SHAPING_X/Y` nem os parâmetros de frequência e amortecimento solicitados. Não foram adicionadas macros sem efeito.

Os limites de temperatura do firmware não aumentam a capacidade térmica dos componentes nem substituem a especificação do hotend, termistor, mesa ou fonte. Não use temperaturas acima das permitidas pelo hardware e pelo material.

## Compilação

Com PlatformIO instalado e as dependências do projeto disponíveis:

```powershell
cd Firmware\Mainboard\Marlin-2.1.1_TJC_029\Marlin-2.1.1_TJC_029
pio run -e MKS_E3_V2
```

O alvo `MKS_E3_V2` gera `.pio/build/MKS_E3_V2/ZNP_ROBIN_NANO.bin`.

## Instalação e riscos

Confirme o modelo da placa e siga o procedimento de atualização compatível com sua impressora. Uma gravação incorreta pode impedir a inicialização e exigir um programador externo. O arquivo `bootloader.bin` incluído na raiz é um carregador mínimo de encadeamento, não o bootloader original da Elegoo; consulte o código em `Firmware/Mainboard/Marlin-2.1.1_TJC_029/Marlin-2.1.1_TJC_029/bootloader` e só o grave se souber recuperar a placa.

Firmware modificado ou procedimentos de gravação podem afetar a garantia conforme os termos do fabricante e do vendedor. Verifique esses termos antes de prosseguir. A instalação e o uso são por sua conta e risco; o responsável por este projeto declara não se responsabilizar por danos, falhas ou perda de garantia.

## Licença e origem

Este projeto contém Marlin e configurações derivadas. Consulte `LICENSE` e os avisos/licenças dos componentes incluídos. As modificações deste projeto não são afiliadas nem endossadas pela Elegoo ou pelo projeto oficial Marlin.
