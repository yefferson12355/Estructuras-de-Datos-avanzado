/**
 * PROYECTO: ENJAMBRE DE DRONES PROFESIONAL
 * LÓGICA: ASIGNACIÓN ESPACIAL + STEERING DE 3 ETAPAS
 */

let fuente;
let enjambre = [];
const formaciones = { PUNO: [], PERU: [], LAGO: [], SOL: [] };
const ESTADOS = ['PUNO', 'PERU', 'LAGO', 'SOL'];
let indiceEstado = 0;
let centro;

const CONFIG = {
    MAX_DRONES: 400,
    VELOCIDAD: 10,
    RADIO_COLISION: 10,
    DISTANCIA_FRENADO: 60,
    UMBRAL_FANTASMA: 120 // A esta distancia dejan de chocar para viajar rápido
};

function preload() {
    fuente = loadFont('https://cdnjs.cloudflare.com/ajax/libs/topcoat/0.8.0/font/SourceSansPro-Bold.otf');
}

function setup() {
    createCanvas(windowWidth, windowHeight).parent('canvas-container');
    centro = createVector(width / 2, height / 2);
    
    if (select('#btn-siguiente')) select('#btn-siguiente').mousePressed(cambiarEscena);

    prepararGeometria();
    crearFlota();
    cambiarEscena(); 
}

function draw() {
    background(15, 23, 42);
    enjambre.forEach(d => {
        d.ejecutar(enjambre);
        d.render();
    });
}

function windowResized() {
    resizeCanvas(windowWidth, windowHeight);
    centro.set(width / 2, height / 2);
    actualizarObjetivos();
}

/** * ALGORITMO DE TRASLACIÓN ORDENADA
 * Evita que los drones se crucen en el camino ordenándolos por su posición X.
 */
function actualizarObjetivos() {
    let puntos = formaciones[ESTADOS[indiceEstado]];
    
    // Ordenamos drones y puntos por X para minimizar cruces de trayectorias
    let dronesOrdenados = [...enjambre].sort((a, b) => a.pos.x - b.pos.x);
    let puntosOrdenados = [...puntos].sort((a, b) => a.x - b.x);

    for (let i = 0; i < enjambre.length; i++) {
        let dron = dronesOrdenados[i];
        if (i < puntosOrdenados.length) {
            let p = puntosOrdenados[i];
            dron.fijarMeta(p.x + centro.x, p.y + centro.y, true);
        } else {
            // Mandamos los drones sobrantes al centro, pero apagados
            dron.fijarMeta(centro.x, centro.y, false);
        }
    }
}

function cambiarEscena() {
    indiceEstado = (indiceEstado + 1) % ESTADOS.length;
    actualizarObjetivos();
}

/**
 * GENERACIÓN DE PUNTOS LIMPIOS
 */
function prepararGeometria() {
    const config = { sampleFactor: 0.1 };
    const palabras = ['PUNO', 'PERÚ', 'LAGO', 'SOL'];
    const keys = ['PUNO', 'PERU', 'LAGO', 'SOL'];
    
    palabras.forEach((txt, i) => {
        let b = fuente.textBounds(txt, 0, 0, 200);
        let pts = fuente.textToPoints(txt, -b.w / 2, b.h / 2, 200, config);
        // Convertimos a p5.Vector real para evitar error e.copy
        formaciones[keys[i]] = pts.map(p => createVector(p.x, p.y));
    });
}

function crearFlota() {
    let maxPts = Math.max(...Object.values(formaciones).map(f => f.length));
    for (let i = 0; i < maxPts; i++) {
        enjambre.push(new Dron(random(width), random(height)));
    }
}

/**
 * CLASE DRON: COMPORTAMIENTO AUTÓNOMO
 */
class Dron {
    constructor(x, y) {
        this.pos = createVector(x, y);
        this.vel = createVector(0, 0);
        this.acc = createVector(0, 0);
        this.target = createVector(x, y);
        this.activo = true;
        this.anclado = false;
        this.color = this.pickColor();
    }

    pickColor() {
        let colors = [color('#FF3C3C'), color('#FFD700'), color('#3C96FF')];
        return random(colors);
    }

    fijarMeta(x, y, mostrar) {
        this.target.set(x, y);
        this.activo = mostrar;
        this.anclado = false;
    }

    ejecutar(lista) {
        if (this.anclado) return;

        let distTarget = p5.Vector.dist(this.pos, this.target);
        
        // 1. LLEGADA (Arrive)
        let fuerzaLlegada = this.steerArrive(distTarget);
        this.acc.add(fuerzaLlegada);

        // 2. SEPARACIÓN INTELIGENTE (Solo si está cerca de la meta)
        // Esto evita choques masivos durante el viaje largo
        if (distTarget < CONFIG.UMBRAL_FANTASMA && this.activo) {
            let sep = this.steerSeparation(lista);
            sep.mult(1.5);
            this.acc.add(sep);
        }

        // 3. MOVIMIENTO
        this.vel.add(this.acc);
        this.vel.limit(CONFIG.VELOCIDAD);
        this.pos.add(this.vel);
        this.acc.mult(0);
        this.vel.mult(0.9); // Fricción constante

        // 4. BLOQUEO MAGNÉTICO (Snap)
        if (distTarget < 1.5 && this.vel.mag() < 0.5) {
            this.pos.set(this.target);
            this.vel.mult(0);
            this.anclado = true;
        }
    }

    steerArrive(d) {
        let deseado = p5.Vector.sub(this.target, this.pos);
        let speed = (d < CONFIG.DISTANCIA_FRENADO) ? map(d, 0, CONFIG.DISTANCIA_FRENADO, 0, CONFIG.VELOCIDAD) : CONFIG.VELOCIDAD;
        deseado.setMag(speed);
        let steer = p5.Vector.sub(deseado, this.vel);
        steer.limit(0.8);
        return steer;
    }

    steerSeparation(lista) {
        let steer = createVector(0, 0);
        let count = 0;
        lista.forEach(otro => {
            if (!otro.activo || !otro.visible || otro === this) return;
            let d = p5.Vector.dist(this.pos, otro.pos);
            if (d > 0 && d < CONFIG.RADIO_COLISION) {
                let diff = p5.Vector.sub(this.pos, otro.pos).normalize().div(d);
                steer.add(diff);
                count++;
            }
        });
        if (count > 0) steer.div(count).setMag(CONFIG.VELOCIDAD).sub(this.vel).limit(0.5);
        return steer;
    }

    render() {
        if (!this.activo) return;
        stroke(this.color);
        strokeWeight(6);
        point(this.pos.x, this.pos.y);
    }
}