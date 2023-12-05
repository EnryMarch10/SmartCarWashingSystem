plugins {
    java
    application
    id("com.github.johnrengelman.shadow") version "8.1.1"
    id("org.danilopianini.gradle-java-qa") version "1.6.0"
}

repositories {
    mavenCentral()
}

val javaFXModules = listOf("base", "controls", "fxml", "swing", "graphics")
val supportedPlatforms = listOf("linux", "mac", "win")

dependencies {
    compileOnly("com.github.spotbugs:spotbugs-annotations:4.7.3")

    implementation("org.slf4j:slf4j-api:2.0.9")
    implementation("org.slf4j:slf4j-nop:2.0.9")
    implementation("io.github.java-native:jssc:2.9.5")

    val javaFxVersion = "15"
    for (platform in supportedPlatforms) {
        for (module in javaFXModules) {
            implementation("org.openjfx:javafx-$module:$javaFxVersion:$platform")
        }
    }
}

application {
    mainClass.set("smartcarwashingsystem.TestReceiver")
}