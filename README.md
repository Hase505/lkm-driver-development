# 💻 Desenvolvimento de Drivers com Linux Kernel Module (LKM)

Este repositório tem como objetivo detalhar o meu processo de aprendizado sobre desenvolvimento de drivers Linux. O repositório está subdivido em pequenos projetos, com cada um contendo o código-fonte do módulo do kernel, o Makefile, 
e uma descrição do que significa cada elemento utilizado.

## O que é um driver?

Um driver é uma interface entre o hardware e o sistema operacional. Ele gerencia o hardware e possibilita as interações necessárias para o seu funcionamento. Por exemplo, pode padronizar operações de leitura e escrita em um dispositivo de armazenamento, definir o comportamento de um LED, ou gerenciar uma interface de rede.

No Linux, é possível trabalhar com drivers de duas formas diferentes: através de drivers integrados ao kernel do Linux ou através de módulos do kernel.

### Driver Integrado

Drivers integrados são aqueles compilados diretamente com o código-fonte do kernel. Geralmente, drivers essenciais utilizam essa abordagem. A vantagem é que esses drivers estão disponíveis no momento da inicialização do sistema, mas eles sempre permanecem ativos, mesmo quando não são necessários.

### Drivers através de Módulos

Este repositório foca no desenvolvimento de drivers utilizando módulos do kernel. Módulos podem ser carregados e descarregados dinamicamente, sem a necessidade de reiniciar o sistema ou recompilar o kernel. Essa abordagem oferece maior flexibilidade e economia de recursos, já que os módulos podem ser desativados quando não estão sendo usados.


## Funcionamento do Driver

Drivers criam uma ponte entre o hardware e o sistema operacional, fornecendo uma camada de abstração. No Linux, o kernel oferece as syscalls (chamadas de sistema), que permitem que processos e funções executem operações como leitura, escrita, e conexão com dispositivos.

No Linux, "tudo é um arquivo". Isso significa que dispositivos de hardware, e até conexões de rede, possuem representações na forma de arquivos, geralmente localizados no diretório `/dev/`. O driver, por meio dessas interfaces, fornece uma maneira de os usuários interagirem com o hardware.

## Configurações Iniciais no Raspberry Pi

Utilizei um Raspberry Pi 3b para o desenvolvimento.
As configurações abaixo são necessárias para configurar o ambiente de desenvolvimento no Raspberry Pi:

1. Atualizar o sistema:
   ```bash
   sudo apt update && sudo apt upgrade
2. Instalação dos headers do kernel (pode variar dependendo do sistema operacional):
   ```bash
   sudo apt install -y raspberrypi-kernel-headers 
3. Instalação dos utilitários de compilação, como gcc e make:
   ```bash
   sudo apt install -y build-essential
4. Reinicialização do sistema, caso um novo kernel tenha sido instalado:
   ```bash
   reboot


