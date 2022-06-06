/*
Autor: Eder João Santini
WhatsApp: +55(69)98463-9009
Iniciado: 28/10/2019 (Derivada da LIB ArquivoManutencao v.2.0.3)

Esta LIB axilia na manipulação de arquivos seja no SD ou SPIFFS
*/
#include "FileManager.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//********************************************** Implementação dos métodos da classe *********************************************************************
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* <<<<<<<<< Construtor da Classe >>>>>>>>>>>>>>>>>>>> */
FileManager::FileManager(void){
    /*
    Serial.println("Construtor");
    */
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Compara se as string são iguais >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Compara se as string são iguais
boolean FileManager::_comparaString(String str1, String str2){
    str1.toUpperCase();
    str2.toUpperCase();
    if(str1 == str2) return true;
    else return false;
}

/*  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Inicializa o sistema de arquivos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa o sistema de arquivos
boolean FileManager::_beginFile(boolean sdCard){
    SD.end();
    SPIFFS.end();

    if(sdCard) return SD.begin(SS);
    else       return SPIFFS.begin(true);
}

/* ################################ Metodos privados ##################################################################### */
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Salvar as informações da String no SD ou SPIFF >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Salvar as informações da String no SD ou SPIFF
// - nomeArquivo: Nome do arquivo que receberá as informações a serem salvas.
// - informacao: Informação a ser salva no arquivo.
// - quebraDeLinha: Salva a informação com quebra de linha ou não
// - novoArquivo: Se for 'true' abre o 'nomeArquivo' apagando seu conteudo, se for 'false' abre o 'nomeArquivo' e adiciona nova 'informacao'
// - sdCard: Salva no SD ou SPIFFS
boolean FileManager::_setInformacao(String nomeArquivo, String informacao, boolean quebraLinha, boolean novoArquivo, boolean sdCard){
    String arquivoOpcao = "";

    if(novoArquivo) arquivoOpcao = FILE_WRITE;     // Cria um novo
    else arquivoOpcao = FILE_APPEND;    // Edita o arquivo

    _arquivosManipulacaoAuxiliar.close();    // Se o arquivo estiver aberto feche

    criarDiretorio(_separaNomeDiretorioDoEndereco(nomeArquivo), sdCard); // Se o nome do arquivo cópia tiver diretórios, então crie o diretório antes de copiar o arquivo

    _beginFile(sdCard);
    if(sdCard){    // Se for SD Card
        _arquivosManipulacaoAuxiliar = SD.open(nomeArquivo.c_str(), arquivoOpcao.c_str() );      // Cria um novo arquivo em branco e prepara para salvar
    }else{          // Se for SPIFF
        _arquivosManipulacaoAuxiliar = SPIFFS.open(nomeArquivo.c_str(), arquivoOpcao.c_str() );  // Cria um novo arquivo em branco e prepara para salvar
    }

    if (_arquivosManipulacaoAuxiliar){       // Se foi possível abrir
        if(quebraLinha)                     // Se tiver quebra de linha
            _arquivosManipulacaoAuxiliar.println(informacao);    // Escreve registro com quebra de linha
        else _arquivosManipulacaoAuxiliar.print(informacao);      // Escreve registro com quebra de linha

        _arquivosManipulacaoAuxiliar.close();                // Fecha arquivo
        return true;                    // Retorna true
    }
    return false; 
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna em uma String todos os arquivos no diretório pedido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna em uma String todos os arquivos no diretório pedido
//  File diretorio = Diretorio a ser exibido
//  boolean exibirTamanhoArquivo = Indica se vai ou não ser exibido o tamanho dos arquivos encontrados
//  boolean exibirSubDir = Indica se vai ou não ser exibibo no resultado os subdiretorios encontrado
//  boolean abrirSubDir = Incica se vai ou não ser aberto todos os subdiretorios
//  boolean indentacao  = Incica se vai ou não ter indentação na exibição dos subdiretorios
//  int numeroTab = Número inicial de espaços utilizado na indentação de subdiretório. O valor padrão é zero
String FileManager::_listaArquivosNoDiretorio(File diretotio, boolean exibirTamanhoArquivo, boolean exibirSubDir, boolean abrirSubDir, boolean indentacao, int numeroTab){
    String retorno  = "";
    while(true) {

        File entry =  diretotio.openNextFile();
        if (! entry) {
            // no more files
            // return to the first file in the directory
            diretotio.rewindDirectory();
            break;
        }
        if (indentacao){
            for (uint8_t i=0; i<numeroTab; i++) {
                retorno += " ";
            }
        }
        //retorno += entry.name();
        if (entry.isDirectory()) {
            if(exibirSubDir){
                retorno += entry.name();
                retorno += "/\n";
                if(abrirSubDir) retorno += _listaArquivosNoDiretorio(entry, exibirTamanhoArquivo, exibirSubDir, abrirSubDir, indentacao, numeroTab+1);
            }
        } else {
            retorno += entry.name();
            if (exibirTamanhoArquivo) retorno += " " + String(entry.size());
            retorno += "\n";

        }
    }
    return retorno;
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Remover parte da String >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Remover parte da String.
String FileManager::_removeDaString(String original, String remover){
    original.remove(original.indexOf(remover), original.indexOf(remover) + remover.length());
    return original;
} 
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Separa o nome do diretório do endereço do arquivo  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Separa o nome do diretório do endereço do arquivo
String FileManager::_separaNomeDiretorioDoEndereco(String endereco){
    int     tamanho = endereco.length();
    for(int i=tamanho; i > -1; i--){
        if(endereco[i] == '/'){
            endereco = endereco.substring(0  , i);
            if(endereco[0] != '/') endereco = "/" + endereco;
            return endereco;
        }
    }
    return "";
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<< Localiza o nome do proximo arquivo ou do anterior >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Localiza o nome do arquivo dentro do diretório conforme a opcao escolhida
//  enderecoArquivoOuDiretorio = Caso seja escolhida a opção 'A' ou 'P' deverá ser passado apenas o endereço do diretório;
//                               Caso seja escolhida a opção 'I' ou 'U' deverá ser passado o nome completo com o endereço do arquivo
//  opcões  = Opção de procura
//    A - Retorna o nome do arquivo anterior;
//    P - Retorna o nome do proximo arquivo;
//    I - Retorna o nome do primeiro arquivono diretório;
//    U - Retorna o nome do ultimo arquivo no diretório;
//  sdCard = Escolha se é para manipular do SD ou SPIFFS
String FileManager::_localizaArquivo(String enderecoArquivoOuDiretorio, char opcao, boolean sdCard){

    if(enderecoArquivoOuDiretorio[enderecoArquivoOuDiretorio.length()-1] == '/') enderecoArquivoOuDiretorio = enderecoArquivoOuDiretorio.substring(0, enderecoArquivoOuDiretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(enderecoArquivoOuDiretorio[0] != '/') enderecoArquivoOuDiretorio = "/" + enderecoArquivoOuDiretorio;

    File root;
    _beginFile(sdCard);

    if(sdCard){
        if(SD.exists(enderecoArquivoOuDiretorio))
            root = SD.open(enderecoArquivoOuDiretorio);
        else return "";
    }else{
        root = SPIFFS.open(enderecoArquivoOuDiretorio);
    }

    String diretorio;
    String arquivoNome;
    if(root.isDirectory()){
        diretorio = enderecoArquivoOuDiretorio;
    }else{
        diretorio   = _separaNomeDiretorioDoEndereco(enderecoArquivoOuDiretorio);
        arquivoNome = enderecoArquivoOuDiretorio;
    }
    root.close();

    String listaDeArquivosStr = listaTodosArquivos(diretorio, sdCard, false, false, false, false);
    if(listaDeArquivosStr == "") return "";

    int index = 0;
    if(opcao == 'I'){
        index = listaDeArquivosStr.indexOf('\n');
        return listaDeArquivosStr.substring(0, index);
    }
    else if(opcao == 'U'){
        index = listaDeArquivosStr.lastIndexOf('\n');
        return listaDeArquivosStr.substring(index+1, listaDeArquivosStr.length());
    }else if(opcao == 'A'){
        index = listaDeArquivosStr.indexOf(arquivoNome);
        if ((index < 0)||(arquivoNome == "")) return "";
        else{
            listaDeArquivosStr = listaDeArquivosStr.substring(0, index);
            if(listaDeArquivosStr[listaDeArquivosStr.length()-1] == '\n'){    // Se o ultimo caracter for uma quebra de linha, remova-o
                listaDeArquivosStr = listaDeArquivosStr.substring(0, listaDeArquivosStr.length()-1);
            }
            index = listaDeArquivosStr.lastIndexOf('\n' );
            if(index < 0 ) index = 0;            
            else index += 1;
            return listaDeArquivosStr.substring(index, listaDeArquivosStr.length());
        }
    }else if(opcao == 'P'){
        index = listaDeArquivosStr.indexOf(arquivoNome);
        if ((index < 0)||(arquivoNome == "")) return "";
        else{
            listaDeArquivosStr = listaDeArquivosStr.substring(index +  arquivoNome.length() +1, listaDeArquivosStr.length() );
            index = listaDeArquivosStr.indexOf('\n');
            if(index < 0 ) index = listaDeArquivosStr.length();
            return listaDeArquivosStr.substring(0, index);
        }
    }
    return "";
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa o objeto escolhendo se vai salvar no cartão SD ou SPIFFS e dando um nome
//  No exemplo a baixo será salvo no SD
//  this.begin("arquivo.txt", true);
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::begin(String nomeArquivo, bool sdCard){
    _sdCard = sdCard;
    if(nomeArquivo[0] == '/') _arquivoNome = nomeArquivo; else _arquivoNome = "/" + nomeArquivo; // Se foi esquecido a '/' no inicio do nome do arquivo, será colocado altomáticamente
    return _beginFile(_sdCard);    // Finaliza todos o sistema de arquivos e inicializa novamente conforte a opcao escolhida
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa o objeto dando um nome para o arquivo e acessando o SPIFFS
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::begin(String nomeArquivo){
    return begin(nomeArquivo, false);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa o objeto escolhendo se vai salvar no cartão SD ou SPIFFS
//  No exemplo a baixo será salvo no SD
//  this.begin(true);
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::begin(bool sdCard){
    return begin("/", sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa o objeto acessando o SPIFFS
//  this.begin();
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::begin(){
    return begin("/", false);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<< Verifica se o arquivo ou diretório existe >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Verifica se o arquivo ou diretório existe
boolean FileManager::existe(String endereco, boolean sdCard){
    if(endereco[endereco.length()-1] == '/') endereco.remove(endereco.length()-1, endereco.length());

    if(endereco[0] != '/') endereco = "/" + endereco;
    _beginFile(sdCard);
    if(sdCard) return SD.exists(endereco);
    else return SPIFFS.exists(endereco);

}
//  Verifica se o arquivo ou diretório existe
boolean FileManager::existe(String endereco){
    return existe(endereco, _sdCard);
}
//  Verifica se o arquivo ou diretório existe
boolean FileManager::existe(){
    return existe(_arquivoNome, _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Abre o PRIMEIRO arquivo dentro do diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Abre o PRIMEIRO arquivo dentro do diretório
void FileManager::arquivoAbrirPrimeiro(String diretorio){
    if(diretorio == "") diretorio = _arquivoNome;
    if(diretorio[diretorio.length()-1] == '/') diretorio = diretorio.substring(0, diretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(diretorio[0] != '/') diretorio = "/" + diretorio;

    setNomeArquivo(_localizaArquivo(diretorio, 'I', _sdCard));
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Abre o ULTIMO arquivo dentro do diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Abre o ULTIMO arquivo dentro do diretório
void FileManager::arquivoAbrirUltimo(String diretorio){
    if(diretorio == "") diretorio = _arquivoNome;
    if(diretorio[diretorio.length()-1] == '/') diretorio = diretorio.substring(0, diretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(diretorio[0] != '/') diretorio = "/" + diretorio;

    setNomeArquivo(_localizaArquivo(diretorio, 'U', _sdCard));
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Abre o proximo arquivo dentro do diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Abre o proximo arquivo dentro do diretório
void FileManager::arquivoAbrirProximo(){
    _arquivoNome = _localizaArquivo(_arquivoNome, 'P', _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Abre o arquivo anterior dentro do diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Abre o arquivo anterior dentro do diretório
void FileManager::arquivoAbrirAnterior(){
    _arquivoNome = _localizaArquivo(_arquivoNome, 'A', _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Salvar as informações da String no SD ou SPIFF com quebra de linha >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Salvar as informações da String no SD ou SPIFF com quebra de linha
boolean FileManager::println(String informacao){
    return println(informacao, _arquivoNome, _arquivoNovo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF com quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
boolean FileManager::println(String informacao, String nomeArquivo){
    return println(informacao, nomeArquivo, _arquivoNovo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF com quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
//  - novoArquivo: Se for 'true' será apagado o conteudo do arquivo, se for 'false' o conteudo será apenas EDIDADO;
boolean FileManager::println(String informacao, String nomeArquivo, boolean novoArquivo){
    return println(informacao, nomeArquivo, novoArquivo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF com quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
//  - novoArquivo: Se for 'true' será apagado o conteudo do arquivo, se for 'false' o conteudo será apenas EDIDADO;
//  - sdCard: Salva no SD ou SPIFFS;
boolean FileManager::println(String informacao, String nomeArquivo, boolean novoArquivo, boolean sdCard){
    if(nomeArquivo[0] != '/') nomeArquivo = "/" + nomeArquivo;
    return _setInformacao(nomeArquivo, informacao, true, novoArquivo, sdCard );
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Salvar as informações da String no SD ou SPIFF sem quebra de linha >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Salvar as informações da String no SD ou SPIFF sem quebra de linha
boolean FileManager::print(String informacao){
    return print(informacao, _arquivoNome, _arquivoNovo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF sem quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
boolean FileManager::print(String informacao, String nomeArquivo){
    return print(informacao, nomeArquivo, _arquivoNovo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF sem quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
//  - novoArquivo: Se for 'true' será apagado o conteudo do arquivo, se for 'false' o conteudo será apenas EDIDADO;
boolean FileManager::print(String informacao, String nomeArquivo, boolean novoArquivo){
    return print(informacao, nomeArquivo, novoArquivo, _sdCard);
}
//  Salvar as informações da String no SD ou SPIFF sem quebra de linha
//  escolhendo o nome do arquivo a ser salvo e em qual unidade será salvo.
//  No exemplo a baixo será salvo um novo arquivo na memoria SPIFFS
//  - informacao: Informação a ser salva no arquivo;
//  - nomeArquivo: Nome do arquivo a ser salvo;
//  - novoArquivo: Se for 'true' será apagado o conteudo do arquivo, se for 'false' o conteudo será apenas EDIDADO;
//  - sdCard: Salva no SD ou SPIFFS;
boolean FileManager::print(String informacao, String nomeArquivo, boolean novoArquivo, boolean sdCard){
    if(nomeArquivo[0] != '/') nomeArquivo = "/" + nomeArquivo;
    return _setInformacao(nomeArquivo, informacao, false, novoArquivo, sdCard );
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna se esta utilizando SD ou SPIFF >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna se esta utilizando SD ou SPIFF
boolean FileManager::getSdCard(void){
    return _sdCard;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING
String FileManager::getInformacao(){
    return getInformacao(_arquivoNome, _sdCard);
}
//  Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING
String FileManager::getInformacao(String nomeArquivo){
    return getInformacao(nomeArquivo, _sdCard);
}
//  Retorna o conteudo do arquivo salvo no SD ou SPIFF no formato STRING
String FileManager::getInformacao(String nomeArquivo, boolean sdCard){
    String leitura = "";

    begin(nomeArquivo, sdCard);   // Reatribue as opcoes escolhidas no setup de inicio do objeto
    if(sdCard){    // Se for SD Card
        _arquivosManipulacaoAuxiliar = SD.open(nomeArquivo.c_str(), FILE_READ);    // Abre arquivo para leitura
    }else{          // Se for SPIFF
        _arquivosManipulacaoAuxiliar = SPIFFS.open(nomeArquivo.c_str(), FILE_READ);    // Abre arquivo para leitura
    }

    if(_arquivosManipulacaoAuxiliar.size()<=0){       // Se o arquivo estiver vazio retorna 0
        _arquivosManipulacaoAuxiliar.close();
        return "";
    }    

    while (_arquivosManipulacaoAuxiliar.available()) {   // Enquanto for possivel ler o arquivo
        leitura += _arquivosManipulacaoAuxiliar.readString();
    }

    _arquivosManipulacaoAuxiliar.close();
    return leitura;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Muda o nome do arquivo a ser manipulado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Muda o nome do arquivo a ser manipulado
void FileManager::setNomeArquivo(String nomeArquivo){
    if(nomeArquivo[0] == '/') _arquivoNome = nomeArquivo; else _arquivoNome = "/" + nomeArquivo; // Se foi esquecido a '/' no inicio do nome do arquivo, será colocado altomáticamente    
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Lista todos os arquivos no diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Lista todos os arquivos no diretório
//  String diretorio = Diretório a ser listado
//  boolean sdCard = SD ou SPIFFS
//  boolean exibirTamanhoArquivo = Exibir ou não o tamanho dos arquivos
//  boolean exibirSubDir =  Exeibir ou não os subdiretorios encontrados
//  boolean abrirSubDir = Abrir ou não os subdiretorios
//  boolean indentacao = Ativa ou não a indentação na exebição de subdiretorio
//  Obs. Pode ser mudado o endereço ou unidade a ser listado conferme o exemplo
//  this.listaTodosArquivos("/diretorioTeste", true, true, true, false);
String FileManager::listaTodosArquivos(String diretorio, boolean sdCard, boolean exibirTamanhoArquivo, boolean exibirSubDir, boolean abrirSubDir, boolean indentacao){
    if(diretorio[diretorio.length()-1] == '/') diretorio = diretorio.substring(0, diretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(diretorio[0] != '/') diretorio = "/" + diretorio;

    String retorno;
    File root;

    _beginFile(sdCard);    // Finaliza todos o sistema de arquivos e inicializa novamente conforte a opcao escolhida

    if(sdCard){
        root = SD.open(diretorio.c_str());
        retorno = _listaArquivosNoDiretorio(root, exibirTamanhoArquivo, exibirSubDir, abrirSubDir, indentacao);
        
    }else{
        String  nomeArquivo;
        int     index;

        root = SPIFFS.open(diretorio.c_str());
        File file = root.openNextFile();

        while(file){
            nomeArquivo = file.name();
            index = nomeArquivo.indexOf('/', diretorio.length()+1);
            if((!exibirSubDir) && (index < 0)){
                retorno += nomeArquivo;
                if(exibirTamanhoArquivo) retorno += " " + String(file.size());
                retorno += "\n";
            }else if(exibirSubDir){
                retorno += nomeArquivo;
                if(exibirTamanhoArquivo) retorno += " " + String(file.size());
                retorno += "\n";
            }
            file = root.openNextFile();
        }  
    }

    if(retorno[retorno.length()-1] == '\n'){    // Se o ultimo caracter for uma quebra de linha, remova-o
        retorno = retorno.substring(0, retorno.length()-1);
    }

    root.close();
    return retorno;
}
//  Lista todos os arquivos no diretório
//  Obs. Pode ser mudado o endereço a ser listado conferme o exemplo
//  this.listaTodosArquivos("/diretorioTeste");
String FileManager::listaTodosArquivos(String diretorio){
    return listaTodosArquivos(diretorio, _sdCard);
}
//  Lista todos os arquivos no diretório
String FileManager::listaTodosArquivos(){
    return listaTodosArquivos(_separaNomeDiretorioDoEndereco(_arquivoNome));
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Lista o nome do PRIMEIRO arquivo no diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Lista o nome do PRIMEIRO arquivo no diretório
String FileManager::listaPrimeiroArquivoNome(String diretorio){
    if(diretorio == "") diretorio = _arquivoNome;
    return _localizaArquivo(diretorio, 'I', _sdCard); 
}
//  Lista o nome do PRIMEIRO arquivo no diretório
//  this.listaPrimeiroArquivoNome("/diretorio", true);
String FileManager::listaPrimeiroArquivoNome(String diretorio, boolean sdCard){
    return _localizaArquivo(diretorio, 'I', sdCard); 
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Lista o nome do ULTIMO arquivo no diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Lista o nome do ULTIMO arquivo no diretório
String FileManager::listaUltimoArquivoNome(String diretorio){
    if(diretorio == "") diretorio = _arquivoNome;
    return _localizaArquivo(diretorio, 'U', _sdCard);
}
//  Lista o nome do ULTIMO arquivo no diretório
//  this.listaUltimoArquivoNome("/diretorio", true);
String FileManager::listaUltimoArquivoNome(String diretorio, boolean sdCard){
    if(diretorio == "") diretorio = _arquivoNome;
    return _localizaArquivo(diretorio, 'U', sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<< Lista o nome arquivo ANTERIOR no diretório, segundo a selecao atual >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Lista o nome arquivo ANTERIOR no diretório, segundo a selecao atual
String FileManager::listaAnteriorArquivoNome(String nomeArquivo, boolean sdCard){
    return _localizaArquivo(nomeArquivo, 'A', sdCard);
}
//  Lista o nome arquivo ANTERIOR no diretório, segundo a selecao atual
String FileManager::listaAnteriorArquivoNome(String nomeArquivo){
    if(nomeArquivo == "") nomeArquivo = _arquivoNome;
    return _localizaArquivo(nomeArquivo, 'A', _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<< Lista o nome PROXIMO arquivo no diretório, segundo a selecao atual >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Lista o nome PROXIMO arquivo no diretório, segundo a selecao atual
String FileManager::listaProximoArquivoNome(String nomeArquivo, boolean sdCard){
    return _localizaArquivo(nomeArquivo, 'P', sdCard);
}
//  Lista o nome PROXIMO arquivo no diretório, segundo a selecao atual
String FileManager::listaProximoArquivoNome(String nomeArquivo){
    if(nomeArquivo == "") nomeArquivo = _arquivoNome;
    return _localizaArquivo(nomeArquivo, 'P', _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Apaga todos os arquivos no diretório especifico >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Apaga todos os arquivos no diretório especifico no SD ou SPIFFS
//  this.removerArquivoTodosNoDiretorio("/diretorioTeste", true);
boolean FileManager::removerArquivoTodosNoDiretorio(String diretorio, boolean sdCard){
    boolean retorno = false;
    if(diretorio[diretorio.length()-1] == '/') diretorio = diretorio.substring(0, diretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(diretorio[0] != '/') diretorio = "/" + diretorio;

    File root;

    _beginFile(sdCard);    // Finaliza todos o sistema de arquivos e inicializa novamente conforte a opcao escolhida

    if(sdCard){
        root = SD.open(diretorio);
    }else{
        root = SPIFFS.open(diretorio);
    }
    File file = root.openNextFile();

    do{
        if(sdCard){
            if(!file.isDirectory()) retorno = SD.remove(file.name());
        }else{
            retorno = SPIFFS.remove(file.name());
        }
        file = root.openNextFile();
    }while(file);

    root.close();
    file.close();
    return retorno;
}
//  Apaga todos os arquivos no diretório especifico
//  this.removerArquivoTodosNoDiretorio("/diretorioTeste");
boolean FileManager::removerArquivoTodosNoDiretorio(String diretorio){
    return removerArquivoTodosNoDiretorio(diretorio, _sdCard);
}
//  Apaga todos os arquivos no diretório no qual esta o arquivo vinculado
boolean FileManager::removerArquivoTodosNoDiretorio(){
    return removerArquivoTodosNoDiretorio(_separaNomeDiretorioDoEndereco(_arquivoNome), _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Remove diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Remove diretório
//  this.removerDiretorio("/diretorioTeste");
boolean FileManager::removerDiretorio(String diretorio){
    return removerDiretorio(diretorio, _sdCard);
}
//  Remove diretório no SD ou SPIFFS
//  this.removerDiretorio("/diretorioTeste", true);
boolean FileManager::removerDiretorio(String diretorio, boolean sdCard){
    if(diretorio[diretorio.length()-1] == '/') diretorio = diretorio.substring(0, diretorio.length()-1);    // Se tiver '/' no final da variável diretorio, será removida
    if(diretorio[0] != '/') diretorio = "/" + diretorio;
    boolean retorno = false;

    String listaDeArquivosStr = listaTodosArquivos(diretorio, sdCard, false, true, true, false);
    if(listaDeArquivosStr == "") retorno = false;
    else retorno = true;

    if(listaDeArquivosStr[listaDeArquivosStr.length()-1] == '\n') listaDeArquivosStr.remove(listaDeArquivosStr.length()-1, listaDeArquivosStr.length());

    int indexI;
    int indexF;

    String nomeArquivoOuDiretorio;
    _beginFile(sdCard);
    while(retorno){
        indexI = listaDeArquivosStr.lastIndexOf('\n');
        indexF = listaDeArquivosStr.length();

        if(indexF == 0) break;

        nomeArquivoOuDiretorio = listaDeArquivosStr.substring(indexI+1, indexF);
        if(indexI < 0) indexI = 0;

        listaDeArquivosStr.remove(indexI, indexF);

        if(nomeArquivoOuDiretorio[nomeArquivoOuDiretorio.length()-1] == '/'){
            nomeArquivoOuDiretorio.remove(nomeArquivoOuDiretorio.length()-1, nomeArquivoOuDiretorio.length());
            if(sdCard) retorno = SD.rmdir(nomeArquivoOuDiretorio);

        }else{
            if(sdCard) retorno = SD.remove(nomeArquivoOuDiretorio);
            else retorno = SPIFFS.remove(nomeArquivoOuDiretorio);
        }
    }

    if(sdCard && (diretorio!="/")) retorno = SD.rmdir(diretorio);

    return retorno;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna o nome do arquivo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna o nome do arquivo
String FileManager::getNomeArquivo(){
    return _arquivoNome;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Sempre que for salvar informações no arquivo, será apagado seu conteudo >>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Sempre que for salvar informações no arquivo, será apagado seu conteudo
void FileManager::novoArquivoEnabled(void){
    _arquivoNovo = true;
}
/* <<<<<<<<<<< Sempre que for salvar informações no arquivo, será salvo no final do arquivo sem que seja apagado seu conteudo (editar). >>>>>>>>>>>>> */
//  Sempre que for salvar informações no arquivo, será salvo no final do arquivo sem que seja apagado seu conteudo (editar).
void FileManager::novoArquivoDisable(void){
    _arquivoNovo = false;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna se é para CRIAR UM NOVO arquivo ou EDITAR >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna se é para CRIAR UM NOVO arquivo ou EDITAR no momento de salvar informações pelo método 'this.print' ou 'this.println'
boolean FileManager::getNovoArquivo(){
    return _arquivoNovo;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna o tamanho do arquivo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna o tamanho do arquivo
int FileManager::getTamanhoArquivo(){
    return getTamanhoArquivo(_arquivoNome, _sdCard);
}
//  Retorna o tamanho do arquivo
//  this.getTamanhoArquivo("/arquivo.txt");
int FileManager::getTamanhoArquivo(String nomeArquivo){
    return getTamanhoArquivo(nomeArquivo, _sdCard);
}
//  Retorna o tamanho do arquivo
//  this.getTamanhoArquivo("/arquivo.txt", true);
int FileManager::getTamanhoArquivo(String nomeArquivo, boolean sdCard){
    if(nomeArquivo[0] != '/') nomeArquivo = "/" + nomeArquivo;

    File root;
    int tamanhoArquivo = 0;
    _beginFile(sdCard);
    if(sdCard){
        root = SD.open(nomeArquivo.c_str());
        tamanhoArquivo = root.size();
        root.close();
    }else{
        root = SPIFFS.open(nomeArquivo.c_str());
        tamanhoArquivo = root.size();
        root.close();
    }
    return tamanhoArquivo;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna quanto de espaço em memoria tem no total >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna quanto de espaço em memoria tem no total
int FileManager::getEspacoTotal(void){
    return getEspacoTotal(_sdCard);
}
//  Retorna quanto de espaço em memoria tem no total
int FileManager::getEspacoTotal(boolean sdCard){
    _beginFile(sdCard);
    if(sdCard)
       return SD.totalBytes();
    else
       return SPIFFS.totalBytes();
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Retorna quanto de espaço foi utilizado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna quanto de espaço foi utilizado
int FileManager::getEspacoUtilizado(){
    return getEspacoUtilizado(_sdCard);
}
//  Retorna quanto de espaço foi utilizado
int FileManager::getEspacoUtilizado(boolean sdCard){
    _beginFile(sdCard);
    if(sdCard)
       return SD.usedBytes();
    else
       return SPIFFS.usedBytes();
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna quanto de espaço tem disponivel em memória >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna quanto de espaço tem disponivel
int FileManager::getEspacoDisponivel(){
    return getEspacoDisponivel(_sdCard);
}
//  Retorna quanto de espaço tem disponivel
int FileManager::getEspacoDisponivel(boolean sdCard){
    _beginFile(sdCard);
    if(sdCard)
       return SD.totalBytes() - SD.usedBytes();
    else
       return SPIFFS.totalBytes() - SPIFFS.usedBytes();
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Remove o arquivo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Remove o arquivo informado e retorna se deu tudo certo na remoção
//  this.removeArquivo("/teste.txt", true);
boolean FileManager::removerArquivo(String nomeArquivo, boolean sdCard){
    if(nomeArquivo[0] != '/') nomeArquivo = "/" + nomeArquivo;
    _beginFile(sdCard);
    if(sdCard)
       return SD.remove(nomeArquivo.c_str());
    else
       return SPIFFS.remove(nomeArquivo.c_str());
}
//  Remove o arquivo informado e retorna se deu tudo certo na remoção
//  this.removeArquivo("/teste.txt");
boolean FileManager::removerArquivo(String nomeArquivo){
    return removerArquivo(nomeArquivo, _sdCard);
}
//  Remove o arquivo vinculado e retorna se deu tudo certo na remoção
//  this.removeArquivo();
boolean FileManager::removerArquivo(void){
    return removerArquivo(_arquivoNome);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Renomeia o arquivo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Renomeia o arquivo
//  this.renomear("/arquivoOrigem.txt", "/arquivoNovoNome.txt", true);
boolean FileManager::renomear(String arquivoOrigem, String arquivoNovoNome, boolean sdCard){
    if(arquivoNovoNome[0] != '/') arquivoNovoNome = "/" + arquivoNovoNome;
    _beginFile(sdCard);
    if(sdCard)
       return SD.rename(arquivoOrigem.c_str(), arquivoNovoNome.c_str());
    else
       return SPIFFS.rename(arquivoOrigem.c_str(), arquivoNovoNome.c_str());
}
//  Renomeia o arquivo
//  this.renomear("/arquivoNovoNome.txt");
boolean FileManager::renomear(String arquivoNovoNome){
    return renomear(_arquivoNome, arquivoNovoNome, _sdCard );
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Copiar o arquivo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Faz uma cópia do arquivo selecionado com um dos seguintes procedimentos this.begin("/arquivo.txt"); ou this.setNomeArquivo("/arquivo.txt");
//  para o nome do novo arquivo escolhido para cópia.
//  this.copiar("/arquivoCopia.txt");
//  Obs. Existe outras formas de se efetuar uma cópia de arquivo. Veja as opções em 'ArquivoManipulcao.h'
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::copiar(String nomeArquivoCopia){
    return copiar(nomeArquivoCopia, _sdCard);
}
//  Copia o arquivo para o SD ou SPIFFS conforme a opção escolhida.
//  Obs. O nome do arquivo de oringem pode ter sido selecionado com um dos
//  seguintes procedimentos this.begin("/arquivo.txt"); ou this.setNomeArquivo("/arquivo.txt");
//  this.copiar("/arquivoCopia.txt", false);
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::copiar(String nomeArquivoCopia, boolean sdCard){
    return copiar(_arquivoNome, nomeArquivoCopia, sdCard);
}
//  Copia o arquivo de SD para SPIFFS ou SPIFFS para SD, sendo passado por parametro o nome do arquivo original,
//  o nome de cópia e o local salvo.
//  this.copiar("\arquivoTeste.txt", "\copia.txt", true);
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::copiar(String nomeArquivoOriginal, String nomeArquivoCopia, boolean sdCard){
    return copiar(nomeArquivoOriginal, _sdCard, nomeArquivoCopia, sdCard );
}
//  Copia o arquivo de SD para SPIFFS ou SPIFFS para SD, sendo passado por parametro o nome do arquivo original,
//  se o arquivo original esta no SD, o nome de cópia e o local salvo.
//  this.copiar("\arquivoTeste.txt", true, "\copia.txt", false);
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::copiar(String nomeArquivoOriginal, boolean sdCardOrigem, String nomeArquivoCopia, boolean sdCardCopia){
    if(nomeArquivoCopia[0] != '/') nomeArquivoCopia = "/" + nomeArquivoCopia;
    
    criarDiretorio(_separaNomeDiretorioDoEndereco(nomeArquivoCopia), sdCardCopia); // Se o nome do arquivo cópia tiver diretórios, então crie o diretório antes de copiar o arquivo

    _beginFile(sdCardOrigem);
    if(!_arquivosManipulacaoAuxiliar){       // Se o ponteiro estiver nulo  
        if(sdCardOrigem){    // Se for SD Card
            _arquivosManipulacaoAuxiliar = SD.open(nomeArquivoOriginal.c_str(), FILE_READ);    // Abre arquivo para leitura
        }else{          // Se for SPIFF
            _arquivosManipulacaoAuxiliar = SPIFFS.open(nomeArquivoOriginal.c_str(), FILE_READ);    // Abre arquivo para leitura
        }

        if(!_arquivosManipulacaoAuxiliar){     // Se aconteceu algum erro 
            _arquivosManipulacaoAuxiliar.close();
            return false;  
        }
    }else{
        return false;
    }

    if(_arquivosManipulacaoAuxiliar.size()<=0){       // Se o arquivo estiver vazio retorna 0
        _arquivosManipulacaoAuxiliar.close();
        return false;
    }

    if( (_comparaString(nomeArquivoOriginal, nomeArquivoCopia)) && (sdCardOrigem == sdCardCopia) ){   // Não é possivel copiar um arquivo na mesma unidade com o mesmo nome.
        _arquivosManipulacaoAuxiliar.close();
        return false;
    }

    File arquivoCopia;
    if(_arquivosManipulacaoAuxiliar){
        if(sdCardCopia){ // Salvar no cartão SD
            SD.begin(SS);
            arquivoCopia = SD.open(nomeArquivoCopia.c_str(), FILE_WRITE);
            if(!SD.exists(nomeArquivoCopia.c_str()) ) return false;               // Se por algum motivo não foi possivel criar o arquivo return false;
        }else{      // Salvar no SPIFFS
            SPIFFS.begin(true);
            arquivoCopia = SPIFFS.open(nomeArquivoCopia.c_str(), FILE_WRITE);
            if(!SPIFFS.exists(nomeArquivoCopia.c_str()) ) return false;           // Se por algum motivo não foi possivel criar o arquivo return false;
        }

        if( arquivoCopia ){   // Se foi possivel 
            char leitura;     // Variavel que guarda o caracter lido do arquivo 
            while(_arquivosManipulacaoAuxiliar.available()){
                leitura = _arquivosManipulacaoAuxiliar.read();
                arquivoCopia.print(leitura);
            }
        }else{  // Se não foi possivel criar o arquivo na unidade de destino, retorne false;
            return false;
        }
    }else{
        return false;
    }
    arquivoCopia.close();
    _arquivosManipulacaoAuxiliar.close();

    return true;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Criar um novo diretório >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Criar um novo diretório escolhendo se vai ser no SD ou SPIFFS
//  this.criarDiretorio("/novoDir", true);
boolean FileManager::criarDiretorio(String novoDiretorio, boolean sdCard){
    if(novoDiretorio[novoDiretorio.length()-1] == '/') novoDiretorio = novoDiretorio.substring(0, novoDiretorio.length()-1);    // Se tiver '/' no final da variável novoDiretorio, será removida
    if(novoDiretorio[0] != '/') novoDiretorio = "/" + novoDiretorio;            // Se tiver não tiver '/' no inicio da variável novoDiretorio, será adicionado '/'

    _arquivosManipulacaoAuxiliar.close();    // Se o arquivo estiver aberto feche

    _beginFile(sdCard);
    if(sdCard){    // Se for SD Card
        if(novoDiretorio != ""){ // Se tiver endereço de diretório antes no nome do arquivo, crie o diretório
            int tamanho = novoDiretorio.length();
            for(int i = 1; i < tamanho; i++ ){
                if(novoDiretorio[i] == '/'){
                    SD.mkdir(novoDiretorio.substring(0, i));
                }
            }
            return SD.mkdir(novoDiretorio);
        }else{
            return false;
        }
    }else{          // Se for SPIFF
        return SPIFFS.begin(true);
    }
}
//  Criar um novo diretório escolhendo vinculado ao SD ou SPIFFS conforme a opção escolhida no begin
//  this.criarDiretorio("/novoDir");
boolean FileManager::criarDiretorio(String novoDiretorio){
    return criarDiretorio(novoDiretorio, _sdCard);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<< Copia um diretório inteiro de SD para SPIFFS, SPIFFS para SD, SD para SD ou SPIFFS para SPIFFS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
//  Copia um diretório inteiro de SD para SPIFFS, SPIFFS para SD, SD para SD ou SPIFFS para SPIFFS
//  ATENÇÃO - Arquivos salvos em SPIFFS não podem ter seus nomes com mais de 31 caracteres.
boolean FileManager::copiarDiretorio(String nomeDirOriginal, boolean sdCardOrigem, String nomeDirCopia, boolean sdCardCopia){
    if(nomeDirOriginal[nomeDirOriginal.length()-1] != '/') nomeDirOriginal += "/";
    if(nomeDirCopia[nomeDirCopia.length()-1] != '/') nomeDirCopia += "/";

    if(nomeDirOriginal[0] != '/') nomeDirOriginal = "/" + nomeDirOriginal;
    if(nomeDirCopia[0]    != '/') nomeDirCopia    = "/" + nomeDirCopia;

    boolean retorno = false;
    if(existe(nomeDirOriginal, sdCardOrigem)) retorno = criarDiretorio(nomeDirCopia, sdCardCopia);

    String nomeArquivoOuDiretorio;
    String listaDeArquivosStr = listaTodosArquivos(nomeDirOriginal, sdCardOrigem, false, true, true, false);

    // ----------------------- Lista de arquivos que não podem ser copiados -----------------------------------------
    listaDeArquivosStr = _removeDaString(listaDeArquivosStr, "/System Volume Information/\n");
    listaDeArquivosStr = _removeDaString(listaDeArquivosStr, "/System Volume Information/WPSettings.dat\n" );
    listaDeArquivosStr = _removeDaString(listaDeArquivosStr, "/System Volume Information/IndexerVolumeGuid\n" );
    // --------------------------------------------------------------------------------------------------------------

    if(listaDeArquivosStr == "") retorno = false;

    int indexI = 0;
    int indexF = 1;

    while(retorno){
        indexF = listaDeArquivosStr.indexOf('\n', indexI);

        if(indexF < 0 ) indexF = listaDeArquivosStr.length();
        nomeArquivoOuDiretorio = listaDeArquivosStr.substring(indexI, indexF);

        if(nomeArquivoOuDiretorio == "") break;
        if(nomeArquivoOuDiretorio[nomeArquivoOuDiretorio.length()-1] == '/'){
            retorno = criarDiretorio(nomeDirCopia + _removeDaString(nomeArquivoOuDiretorio, nomeDirOriginal ), sdCardCopia);
        }else{
            retorno = copiar(nomeArquivoOuDiretorio, sdCardOrigem, nomeDirCopia + _removeDaString(nomeArquivoOuDiretorio, nomeDirOriginal ), sdCardCopia );
        }
        indexI = indexF +1;
    }
    return retorno;
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna uma variavel do tipo File apos os testes e associações >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Retorna uma variavel do tipo File apos os testes e associações
//  Parametros:
//  nomeArquivo - Nome do arquivo
//  novoArquivo - Cria um novo arquivo sem conteudo
//  editar  -  Se for 'false', abre o arquivo no inicio permitindo apenas leitura, caso seja 'true', abre o arquivo final permitindo a escrita.
//  sdCard - Salva no SD ou SPIFFS
File FileManager::getFile(String nomeArquivo, boolean novoArquivo, boolean editar, boolean sdCard ){
    _arquivoNome = nomeArquivo;
    if(nomeArquivo[0] != '/') nomeArquivo = "/" + nomeArquivo;

    _beginFile(sdCard);
    if(sdCard)
        if(novoArquivo)
            return SD.open(nomeArquivo.c_str(), FILE_WRITE);
        else if(editar)
            return SD.open(nomeArquivo.c_str(), FILE_APPEND);
        else
            return SD.open(nomeArquivo.c_str(), FILE_READ);
    else
        if(novoArquivo)
            return SPIFFS.open(nomeArquivo.c_str(), FILE_WRITE);
        else if(editar)
            return SPIFFS.open(nomeArquivo.c_str(), FILE_APPEND);
        else
            return SPIFFS.open(nomeArquivo.c_str(), FILE_READ);
}
//  Retorna uma variavel do tipo File apos os testes e associações
//  Parametros:
//  editar  -  Se for 'false', abre o arquivo no inicio permitindo apenas leitura, caso seja 'true', abre o arquivo final permitindo a escrita.
File FileManager::getFile(boolean editar){
    return getFile(_arquivoNome, false, editar, _sdCard);
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 