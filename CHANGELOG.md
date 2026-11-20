# Histórico de versões

## v1.0.0

- Firmware para Elegoo Neptune 3 Pro / placa MKS Robin E3 V2 (`MKS_E3_V2`, STM32F401RC), baseado na árvore Marlin 2.1.1 incluída no projeto.
- Ajustados passos por unidade para `{80, 80, 400, 415}`.
- Ajustados feedrates máximos para `{500, 500, 20, 45}` mm/s.
- Ajustadas acelerações máximas para `{5000, 5000, 100, 3000}` mm/s²; aceleração padrão `4000`, retração `3000` e deslocamento `5000` mm/s².
- Definidos os limites de firmware do hotend em `315` °C e da mesa em `120` °C. Esses limites não certificam que o hardware possa operar com segurança nessas temperaturas.
- Desativado Classic Jerk e definido Junction Deviation em `0.04` mm.
- Linear Advance habilitado com K inicial `0.00`; StealthChop desligado em X/Y e ligado em Z/E.
- Adaptive Step Smoothing habilitado.
- Input Shaping não incluído: a versão do Marlin presente no pacote não implementa as opções solicitadas.
- Binário publicado: `ZNP_ROBIN_NANO.bin`.
