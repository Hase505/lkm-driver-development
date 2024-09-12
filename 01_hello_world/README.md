# Criação de um Hello World utilizando LKM
O módulo exibe uma mensagem nos logs do kernel ao ser carregado nele e outra ao ser descarregado.

### Headers
Primeiramente, é necessário incluir no código-fonte as bibliotecas necessárias para o desenvolvimento.
Esses headers irão acompanhar todo desenvolvimento de módulo para o kernel, com ambas sendo essenciais, definindo funções, macros e estruturas básicas.

- `#include <linux/module.h>`
  Principais definições: macros de metadados do módulo e macros para definir a função de entrada e saída (module_init e module_exit)
  
- `#include <linux/init.h`
  Principais definições: macros __init e __exit utilizada na declaração de funções, tem o objetivo de instruir o compilador a colocar a função em um região de memória específica. A principal vantagem
  é a desalocação de memória depois que a função não é mais utilizada.

### Metadados
É necessário incluir algumas informações sobre o módulo no código-fonte, como nome do autor, versão do módulo, licença pela qual o módulo foi escrito, descrição do módulo, etc.
- `MODULE_LICENSE("GPL")`
  É essencial inserir a licença. Se não for inserida ou for inserida uma licença proprietária, algumas funções do kernel serão limitadas para o módulo. Além disso, algumas distribuições
  só carregam os módulos que estão sob certa licença. A GPL (GNU Public License) é uma licença amplamente utilizada e aceita pelas distribuições Linux, por isso, será utilizada.
- `MODULE_AUTHOR`
  Informa o nome do autor.
- `MODULE_VERSION("Versão")`
  Informa a versão do módulo. É utilizada para fins de gerenciamento de módulos, permitindo verificar qual módulo é mais recente.
- `MODULE_DESCRIPTION("Descrição")`
  Exibe uma descrição sobre o que o módulo faz.

### Comentários de funções
É considerado uma boa prática fazer comentários detalhados sobre o comportamento das funções definidas no código.
- Exemplo de um comentário inserido antes da função:
  
  ```c
  /*  *
   * configure_device - Configures the hardware device with given parameters. 
   * @param reg_offset: The offset from the base address to the specific register. 
   * @param value: The value to write to the register. 
   * 
   * Returns: 0 on success, or a negative error code on failure. 
   * 
   * Details: This function writes the specified value to a register located 
   * at the base address plus the given offset. It checks if the base address 
   * is valid and if the write operation succeeds. Errors are logged using 
   * printk(). 
   */

### Módulo básico
Todo LKM deve possuir uma função de entrada e outra de saída. Além disso, é necessário passar essas funções como argumento das macros init_module e exit_module.
- Função de entrada:
```c
static __init int init_function(void)
{
	printk("Hello world!\n");
	return 0;
}
```
A função de entrada retorna um inteiro como código de saída. Se ocorrer algum erro, retornar um inteiro negativo como -1.

- Função de saída:
```c
static __exit void exit_function(void)
{
	printk("Goodbye world!\n");
}
```
A função de saída não possui código de resposa, visto que ela busca apenas desalocar os recursos alocados. O kernel supõe que será um sucesso, já que isso depende
da responsabilidade e habilidade do programador em manter o módulo num estado consistente para ser removido. No caso da função de entrada, fatores externos podem causar erros, como algum problema no hardware e, por isso, 
precisar lidar com erros. Em último caso, se for necessário lidar com erros na função de saída, trabalhar com printk.

- printk() -
  A função printk funciona de forma semelhante ao printf, mas o texto só pode ser visto nas mensagens de log com o utilitário `dmesg`

- Prefixo static em funções -
  Utilizado para definir o escopo da função. Ela só pode ser referenciado no arquivo que ela for definida, evitando conflitos de nomes.

### Makefile
`make` é um utilitário para automatizar o processo de compilação de programas. Ele funciona baseado em regras e dependências. 
No projeto, haverá um arquivo chamado “Makefile”, que define como cada elemento do projeto deve ser compilado, o que deve ser limpado após a compilação, etc. 
Após a criação do makefile, basta executar o comando `make`, que o projeto será compilado. Sua principal vantagem é a de que ele não precisa recompilar todo o projeto novamente, caso necessário. 
Se houve alguma alteração, recompila apenas os arquivos alterados.

```Makefile
obj-m += helloworld.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

- `obj-m` é uma variável que recebe o `helloworld.o`.
Esta variável é específica do sistema de construção do kernel. Ela lista os arquivos objeto que farão parte do módulo a ser compilado.
- `all` é uma regra padrão em Makefiles. Ela define a meta principal a ser atingida quando você executa `make` sem nenhum alvo específico.
- `make -C` muda o diretório de trabalho para o diretório especificado.
- `/lib/modules/$(shell uname -r)/build` é o diretório de construção do kernel, onde os módulos são normalmente construídos. O comando `uname -r` obtém o nome do kernel em execução.
- ` M=$(PWD)` define a variável M como o diretório de trabalho atual (PWD). Essa variável indica ao sistema de construção onde encontrar os arquivos fonte do módulo.
- `modules` chama a meta modules dentro do sistema de construção do kernel, que irá compilar o módulo e instalá-lo.

- `clean` é uma outra regra padrão, define a meta para limpar os arquivos gerados durante a construção.
- `make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean` é similar à regra all, mas chama a meta `clean` dentro do sistema de construção do kernel, removendo os arquivos objeto e o módulo compilado.

#### Construção
Quando o Makefile é executado:
1. Muda para o diretório de construção do kernel.
2. Define o diretório atual como a localização dos seus arquivos fonte.
3. Chama a meta modules do sistema de construção do kernel para compilar o módulo mymodule.c e instalá-lo.

#### Como compilar e verificar
```bash
make
```
Para compilar.

```bash
sudo insmod helloworld.ko
```
Para carregar o módulo no kernel.

```bash
lsmod | grep helloworld
```
Para verificar o módulo carregado.

```bash
dmesg | tail
```
Para verificar as últimas mensagens do kernel, mostrando o Hello World do módulo criado.

```bash
sudo rmmod helloworld
```
Para remover o módulo. Caso visualize as mensagens do kernel novamente, será possível visualizar o Goodbye da função de saída.

### Modprobe
É um utilitário que pode ser utilizado para carregar e descarregar módulos no kernel. É mais robusto e customizável em relação ao insmod e rmmod. Também resolve dependências do módulo. 
Além disso, fornece mensagens de erro mais detalhadas.
