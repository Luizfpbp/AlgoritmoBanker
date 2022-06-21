# AlgoritmoBanker
&nbsp;&nbsp; Esse algoritimo depende de dois arquivos para ser executado,</br>
um com os valores máximos de recursos que cada consumidor pode receber, chamado</br>
de 'customer.txt'.</br>
&nbsp;&nbsp; O arquivo deve ser organizado de forma que cada linha representa um customer</br>
e os dados presentes em cada linha são os limites, eles devem ser separados por uma</br>
vírgula apenas.</br>
&nbsp;&nbsp; Ex: 1,3,4</br>
</br>
&nbsp;&nbsp; O segundo arquivo, é o responsável pelos comandos que o código vai executar,</br>
existem 3 comandos possíveis, RQ, RL e * .</br>
&nbsp;&nbsp; O RQ solicita os recursos digitados, sua formatação deve conter o customer que vai</br>
receber os recursos e a quantidade de recursos que devem ser alocados, todos os valores</br>
devem ser separados por um espaço.</br>
&nbsp; Ex:</br>
&nbsp;&nbsp; O customer 0 pede os recursos 0 2 1</br>
&nbsp;&nbsp; RQ 0 0 2 1</br>
    </br>
&nbsp;&nbsp; O RL é o comando de liberar recursos de um customer, sua formatação é idêntica do RQ</br>
&nbsp; Ex:</br>
&nbsp;&nbsp; O customer 2 libera os recursos 4 2 3</br>
&nbsp;&nbsp; RQ 2 4 2 3</br>
    </br>
&nbsp;&nbsp; O * coleta os dados dos recursos máximos, alocados e necessários de cada customer,</br>
só é necessário que o * esteja presente no arquivo</br>
     </br>
&nbsp;&nbsp; Após a compilação do código, ele retorna um binário 'bunker', para a execução do código,</br>
os recursos inicialmente disponíveis antes da execução dos comandos devem ser informados, de</br>
forma que a quantidade de recursos digitada seja a mesma registrada em ambos os arquivos txt.</br>
    Ex de execução:</br>
    ./banker 10 5 7</br>
</br>
&nbsp;&nbsp; Ao executar o código, ele retorna um arquivo 'result.txt'</br>
que contem todos as mensagens de retorno de cada comando do arquivo</br>
'commands.txt'.

&nbsp;&nbsp; IMPLEMENTADO NO LINUX

## Commands
```bash
$ make          # Compila o arquivo c e retorna um executavel banker     
$ make clean    # Remove o arquivo executavel da pasta
$ make remove   # Remove o 'result.txt' gerado pelo código
```
