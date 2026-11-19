# Neptune 3 Pro — Marlin com perfil de alta velocidade

Firmware comunitário não oficial para a Elegoo Neptune 3 Pro, baseado no Marlin 2.1.1 fornecido no pacote deste projeto. O alvo de compilação é `MKS_E3_V2` (STM32F401RC / placa MKS Robin E3 V2).

## Downloads

Baixe `ZNP_ROBIN_NANO.bin` nos **Assets** do release mais recente. O arquivo também está na raiz deste repositório.

## Resultado relatado

Testado o firmware em uma Neptune 3 Pro, com qualidade de impressão e velocidade comparáveis à velocidade padrão de uma Neptune 4 Pro. Esse é um relato de uso, não um benchmark independente nem uma garantia de resultado em outras impressoras, materiais ou configurações.

A compatibilidade com uma versão recente da tela LCD Elegoo. O modelo e a versão exata da tela variante; portanto, a compatibilidade com outras revisões não é garantida.

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
