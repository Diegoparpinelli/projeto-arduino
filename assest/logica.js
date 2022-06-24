class Controle{
    constructor(){
        this.luz="0"
        this.ar="0"
        this.tempArMin=18
        this.tempArMax=32
        this.tempAr=24
        this.btnUp = document.getElementById("tempUp")
        this.btnDown = document.getElementById("tempDown")
        this.chckBoxLuz = document.getElementById("LUZ")
        this.chckBoxAr = document.getElementById("ar")

        
    }

    mostrarTempAr(){
        document.getElementById("mostrarTempAr").innerHTML = this.tempAr
    }
     aumentarTempAr(){
        if(this.tempAr < this.tempArMax){
            fetch(document.URL+'tempup', {
                method: 'GET'})
            this.tempAr++
            document.getElementById("mostrarTempAr").innerHTML = this.tempAr
            console.log(this.tempAr)
        }
        
    }
    diminuirTempAr(){
        if(this.tempAr > this.tempArMin){
            fetch(document.URL+'tempdown', {
                method: 'GET'})
            this.tempAr--
            document.getElementById("mostrarTempAr").innerHTML = this.tempAr
            console.log(this.tempAr)
        }
    }

    ligarLuz(){
        if(this.chckBoxLuz.checked === true){
            console.log("ligar luz")
            fetch(document.URL+'luzon', {
                method: 'GET'})
        } else{
            console.log("desligar luz")
            fetch(document.URL+'luzoff', {
                method: 'GET'})
        }
    }

    ligarAr(){
        if(this.chckBoxAr.checked === true){
            console.log("ligar ar")
            fetch(document.URL+'aron', {
                method: 'GET'})
        } else{
            console.log("desligar ar")
            fetch(document.URL+'aroff', {
                method: 'GET'})
        }
    }
    
    initEvents(){
        this.mostrarTempAr()
        this.btnUp.addEventListener("click", function(){arduino.aumentarTempAr()})
        this.btnDown.addEventListener("click", function(){arduino.diminuirTempAr()})
        this.chckBoxLuz.addEventListener("change",function(){arduino.ligarLuz()})
        this.chckBoxAr.addEventListener("change",function(){arduino.ligarAr()})


    }



}
function teste(){
    console.log("ola")
}

const arduino = new Controle()
arduino.initEvents()
