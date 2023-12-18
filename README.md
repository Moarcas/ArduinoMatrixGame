<h1 align="center">Arduino Matrix Game</h1>

<p align="center">
  <img src="https://github.com/Moarcas/ArduinoMatrixGame/blob/master/game.jpg" alt=" Matrix Game Photo">
</p>

<h2 align="center">Game description</h2>
<p align="center">
This project showcases an engaging game implemented on Arduino, featuring a 16x16 map on a 8x8 matrix display and joystick control. In this game the players can walk around the map and destroy the walls. 
The goal of the player is to destroy the walls as fast as possible to receive life points and pass to the next level. 
</p>  

<details>
  <summary>
    <h2>Backstory about the game</h2>    
  </summary>
  <p>
  Dive into a retro gaming adventure with this Arduino project. Inspired by classics like Space Invaders, it features a 16x16 world on an 8x8 matrix display, joystick-controlled. Navigate menus, shoot walls, and earn points for a engaging       
  experience.
  </p>
</details>

<details>
  <summary>
    <h2>Menu Structure</h2>    
  </summary>
  <ol>
    <li>
      <h4>Start game</h4>
    </li>
    <li>
      <h4>Highscores</h4>
    </li>
    <li>
      <h4>Settings</h4>
      <ul>
        <li>LCD brightness</li>
        <li>LCD contrast</li>
        <li>Matrix brightness</li>
        <li>
          Sound
          <ul>
            <li>Sound ON</li>
            <li>Sound OFF</li>
          </ul>
        </li>
        <li>
          Reset data
          <ul>
            <li>Reset LCD brightness</li>
            <li>Reset LCD contrast</li>
            <li>Reset matrix brightness</li>
            <li>Reset highscores</li>
          </ul>
        </li>
      </ul>
    </li>
    <li>
      <h4>About</h4>
    </li>
    <li>
      <h4>How to play</h4>
    </li>
  </ol>
</details>

<details>
  <summary>
    <h2>Rules of the game</h2>    
  </summary>
  <ul>
    <li>
      <h3>Menu</h3>
      <ul>
        <li>Move the joystick up or down to move through the menu or sub-menu</li>
        <li>Move the joystick left to exit the sub-menu</li>
        <li>Press the joystick to select what is displayed on the lcd</li>
        <li>Press the joystick to exit the brightness setting</li>
      </ul>
    </li>
    <li>
      <h3>Game</h3>
      <ul>
        <li>Move the joystick up, down, left or right to move the player</li>
        <li>Press the joystick to shoot the walls</li>
        <li>If you destroy 5 walls, you get 3 special shoots</li>
        <li>The special shoot fires 3 bullets, two diagonally and one in the direction of the player</li>
        <li>When the game starts, the player has maximum life (100), the player's life decreases progressively</li>
        <li>The player dies when his life reaches 0</li>
        <li>If the player destroys a wall with a normal shot, he receives 1 life point and 1 score point</li>
        <li>If the player destroys a wall with a special shot, he receives 1 life point and 3 score points</li>
        <li>The player aims to accumulate as many points as possible</li>
        <li>Every 50 points earned increases the level of the game</li>
        <li>When the player passes to the next level, he receives 5 life points and his life decreases faster</li>
      </ul>
    </li>
  </ul>  
</details>

<details>
  <summary>
    <h2>Used components</h2>
  </summary>
  <ol>
    <li>Arduino Uno Board</li>
    <li>Led 8x8 matrix</li>
    <li>LCD display</li>
    <li>Joystick</li>
    <li>Buzzer</li>
    <li>Capacitors</li>
    <li>Matrix driver</li>
    <li>Resistors and wires</li>
  </ol>
</details>

<details>
  <summary>
    <h2 align="center">Video</h2>
  </summary>
  <p align="center">
  <a href="https://youtu.be/V6WaHavQ9yE">
    <img src="https://img.youtube.com/vi/V6WaHavQ9yE/maxresdefault.jpg" alt="Watch the video">
  </a>
</p>
</details>



