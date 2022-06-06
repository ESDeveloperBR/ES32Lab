/*
Autor: Eder João Santini
WhatsApp: +55(69)98463-9009
Iniciado: 28/10/2019 (Derivada da LIB ArquivoManutencao v.2.0.3)

Esta LIB axilia na manipulação de arquivos seja no SD ou SPIFFS
*/
// ifndef evita erros de duplicação ao chamar esta lib mais de uma vez
#ifndef FileManager_h
#define FileManager_h

#include <Arduino.h>      /* Biblioteca Arduino (opcional) */
#include <SD.h>
#include <SPIFFS.h>
#include <FS.h>

#define FILEMANAGER_VERSION "2.1.2 update 06/05/2022"   // mm/dd/yyyy

// Classe FileManager e suas funções
class FileManager{
    // Todas as funções desta lib são publicas, mais detalhes em ArquivosManipulacao.cpp
    private:
      File    _arquivosManipulacaoAuxiliar;     /* Ponteiro do arquivo */

      boolean _sdCard = false;                  /* Se estiver true será salvo no cartao SD */
      boolean _arquivoNovo = false;             /* Controla se vai ser criado um arquivo novo ou apenas editar. */
      String  _arquivoNome;                     /* Nome do arquivo a ser manipulado */
      boolean _beginFile(boolean sdCard);       /* Inicializa o sistema de arquivos */
      boolean _setInformacao(String nomeArquivo, String informacao, boolean quebraLinha, boolean novoArquivo, boolean sdCard);  /* Salvar informacoes no SD ou SPIFF */
      String  _separaNomeDiretorioDoEndereco(String endereco);  /* Separa o nome do diretório no endereço do arquivo */
      String  _removeDaString(String original, String remover); /* Remover parte da String. */
      String  _localizaArquivo(String enderecoArquivoOuDiretorio, char opcao, boolean sdCard); /* Localiza o nome do proximo arquivo ou do anterior */
      boolean _comparaString(String str1, String str2);         /* Compara se as string são iguais */
      String  _listaArquivosNoDiretorio(File diretotio, boolean exibirTamanhoArquivo, boolean exibirSubDir, boolean abrirSubDir, boolean indentacao = true, int numeroTab = 0); /* Retorna em uma String todos os arquivos no diretório pedido */
 
    public: 
      FileManager(void);         /* Construtor */

      boolean begin(String nomeArquivo, bool sdCard); /* Inicializa o objeto com o nome do arquivo */
      boolean begin(String nomeArquivo);/* Inicializa o objeto com o nome do arquivo */
      boolean begin(bool sdCard);       /* Inicializa o objeto com o nome do arquivo */
      boolean begin();                  /* Inicializa o objeto com o nome do arquivo */

      boolean existe();                 /* Verifica se o arquivo ou diretório existe */
      boolean existe(String endereco);  /* Verifica se o arquivo ou diretório existe */
      boolean existe(String endereco, boolean sdCard);      /* Verifica se o arquivo ou diretório existe */
      void    arquivoAbrirPrimeiro(String diretorio = "");  /* Abre o PRIMEIRO arquivo dentro do diretório */
      void    arquivoAbrirUltimo(String diretorio = "");    /* Abre o ULTIMO arquivo dentro do diretório */
      void    arquivoAbrirProximo(void);     /* Abre o proximo arquivo dentro do diretório */
      void    arquivoAbrirAnterior(void);    /* Abre o arquivo anterior dentro do diretório */

      boolean println(String informacao = "");                 /* Salvar as informações da String no SD ou SPIFF com quebra de linha */
      boolean println(String informacao, String nomeArquivo);  /* Salvar as informações da String no SD ou SPIFF com quebra de linha */
      boolean println(String informacao, String nomeArquivo, boolean novoArquivo);  /* Salvar as informações da String no SD ou SPIFF com quebra de linha */
      boolean println(String informacao, String nomeArquivo, boolean novoArquivo, boolean sdCard);  /* Salvar as informações da String no SD ou SPIFF com quebra de linha */

      boolean print(String informacao);                      /* Salvar as informações da String no SD ou SPIFF sem quebra de linha */
      boolean print(String informacao, String nomeArquivo);  /* Salvar as informações da String no SD ou SPIFF sem quebra de linha */
      boolean print(String informacao, String nomeArquivo, boolean novoArquivo);  /* Salvar as informações da String no SD ou SPIFF sem quebra de linha */
      boolean print(String informacao, String nomeArquivo, boolean novoArquivo, boolean sdCard);  /* Salvar as informações da String no SD ou SPIFF sem quebra de linha */

      void    novoArquivoEnabled(void);      /* Sempre que for salvar informações no arquivo, será apagado seu conteudo. */
      void    novoArquivoDisable(void);      /* Sempre que for salvar informações no arquivo, será salvo no final do arquivo sem que seja apagado seu conteudo (editar) */

      void    setNomeArquivo(String nomeArquivo);   /* Muda o nome do arquivo a ser manipulado */
    
      boolean getSdCard(void);              /* Retorna se esta utilizando SD ou SPIFF */
      String  getInformacao(void);          /* Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING */
      String  getInformacao(String nomeArquivo);                /* Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING */
      String  getInformacao(String nomeArquivo, boolean sdCard);/* Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING */

      String  getNomeArquivo(void);     /* Retorna o nome do arquivo */
      boolean getNovoArquivo(void);     /* Retorna se é para CRIAR UM NOVO arquivo ou EDITAR */
      int     getTamanhoArquivo(void);  /* Retorna o tamanho do arquivo */
      int     getTamanhoArquivo(String nomeArquivo); /* Retorna o tamanho do arquivo */
      int     getTamanhoArquivo(String nomeArquivo, boolean sdCard); /* Retorna o tamanho do arquivo */
      int     getEspacoTotal(void);           /* Retorna quanto de espaço em memoria tem no total */
      int     getEspacoTotal(boolean sdCard); /* Retorna quanto de espaço em memoria tem no total */
      int     getEspacoUtilizado(void);       /* Retorna quanto de espaço foi utilizado */
      int     getEspacoUtilizado(boolean sdCard); /* Retorna quanto de espaço foi utilizado */
      int     getEspacoDisponivel(void);          /* Retorna quanto de espaço tem disponivel em memória */
      int     getEspacoDisponivel(boolean sdCard);/* Retorna quanto de espaço tem disponivel em memória */

      File    getFile(boolean editar = false); /* Retorna uma variavel do tipo File apos os testes e associações */
      File    getFile(String nomeArquivo, boolean novoArquivo, boolean editar, boolean sdCard); /* Retorna uma variavel do tipo File apos os testes e associações */

      boolean removerArquivo(String nomeArquivo, boolean sdCard); /* Remove o arquivo */
      boolean removerArquivo(String nomeArquivo);                 /* Remove o arquivo */
      boolean removerArquivo(void);                               /* Remove o arquivo */
      boolean removerArquivoTodosNoDiretorio(String diretorio, boolean sdCard);  /* Apaga todos os arquivos no diretório especifico no SD ou SPIFFS */
      boolean removerArquivoTodosNoDiretorio(String diretorio);   /* Apaga todos os arquivos no diretório especifico */
      boolean removerArquivoTodosNoDiretorio();                   /* Apaga todos os arquivos no diretório no qual esta o arquivo vinculado */
      boolean removerDiretorio(String diretorio, boolean sdCard); /* Remove o diretório */
      boolean removerDiretorio(String diretorio);                 /* Remove o diretório */
      boolean criarDiretorio(String novoDiretorio);               /* Criar um novo diretório */
      boolean criarDiretorio(String novoDiretorio, boolean sdCard); /* Criar um novo diretório escolhendo se vai ser no SD ou SPIFFS */

      boolean renomear(String arquivoNovoNome);                   /* Renomeia o arquivo */
      boolean renomear(String arquivoOrigem, String arquivoNovoNome, boolean sdCard); /* Renomeia o arquivo */
      boolean copiar(String nomeArquivoCopia);                    /* Copia o arquivo */
      boolean copiar(String nomeArquivoCopia, boolean sdCard);    /* Copia o arquivo de SD para SPIFFS ou SPIFFS para SD */
      boolean copiar(String nomeArquivoOriginal, String nomeArquivoCopia, boolean sdCard); /* Copia o arquivo de SD para SPIFFS ou SPIFFS para SD */
      boolean copiar(String nomeArquivoOriginal, boolean sdCardOrigem, String nomeArquivoCopia, boolean sdCardCopia);   /* Copia o arquivo de SD para SPIFFS ou SPIFFS para SD */
      boolean copiarDiretorio(String nomeDirOriginal, boolean sdCardOrigem, String nomeDirCopia, boolean sdCardCopia);  /* Copia um diretório inteiro de SD para SPIFFS, SPIFFS para SD, SD para SD ou SPIFFS para SPIFFS */
      String  listaTodosArquivos(String diretorio, boolean sdCard, boolean exibirTamanhoArquivo = false, boolean exibirSubDir = true, boolean abrirSubDir = false, boolean indentacao = true); /* Lista todos os arquivos */
      String  listaTodosArquivos(String diretorio);                       /* Lista todos os arquivos */
      String  listaTodosArquivos(void);                                   /* Lista todos os arquivos */
      String  listaPrimeiroArquivoNome(String diretorio = "");            /* Lista o nome do PRIMEIRO arquivo no diretório */
      String  listaPrimeiroArquivoNome(String diretorio, boolean sdCard); /* Lista o nome do PRIMEIRO arquivo no diretório */
      String  listaUltimoArquivoNome(String diretorio = "");              /* Lista o nome do ULTIMO arquivo no diretório */
      String  listaUltimoArquivoNome(String diretorio, boolean sdCard);   /* Lista o nome do ULTIMO arquivo no diretório */
      String  listaAnteriorArquivoNome(String nomeArquivo, boolean sdCard);/* Lista o nome arquivo ANTERIOR no diretório, segundo a selecao atual */
      String  listaAnteriorArquivoNome(String nomeArquivo = "");          /* Lista o nome arquivo ANTERIOR no diretório, segundo a selecao atual */
      String  listaProximoArquivoNome(String nomeArquivo, boolean sdCard);/* Lista o nome do PROXIMO arquivo no diretório, segundo a selecao atual */
      String  listaProximoArquivoNome(String nomeArquivo = "");           /* Lista o nome do PROXIMO arquivo no diretório, segundo a selecao atual */
      
  };
#endif