import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import glob
from matplotlib.patches import Circle
import os
from matplotlib.widgets import Slider

# Get all configurations from the confs folder
files = glob.glob("confs/c*")
# way to get filenames on any OS (was causing errors on my windows device)
filenames = sorted(
    files,
    key=lambda x: int(os.path.basename(x).replace("conf", ""))
)

# Create a new figure
fig, ax = plt.subplots()
ax.set(xlim=(0, 20), ylim=(0, 20), aspect='equal')

# room for slider
plt.subplots_adjust(bottom=0.18)

# List to hold the circle patches (assume number of circles remains constant)
circles = []

# Initialize the first frame
data = np.loadtxt(filenames[0], skiprows=2, usecols=[1,2,3])
for x, y, r in data:
    circle = Circle((x, y), r, edgecolor='b', facecolor='none')
    circles.append(circle)
    ax.add_patch(circle)

initial_interval = 75
speed_multiplier = 1.0
frame_idx = 0

# Reccurent update of the figure 
def update(_):
    global frame_idx, speed_multiplier
    # Load new data for the frame
    data = np.loadtxt(filenames[frame_idx], skiprows=2, usecols=[1,2,3])
    for patch, (x, y, r) in zip(circles, data):
        # Update circle position and radius
        patch.center = (x, y)
        patch.set_radius(r)

    # advance frames depending on speed
    step = max(1, int(round(speed_multiplier)))
    frame_idx = (frame_idx + step) % len(filenames)

    return circles

ani = FuncAnimation(fig, update, frames=len(filenames), blit=True, interval = initial_interval)

ax_speed = plt.axes([0.15, 0.06, 0.7, 0.03])
speed_slider = Slider(ax_speed, "Speed", valmin=1, valmax=10.0, valinit=1.0)

def on_speed_change(val):
    global speed_multiplier
    speed_multiplier = float(val)
    print("speed_multiplier =", speed_multiplier)

speed_slider.on_changed(on_speed_change)

plt.show()
