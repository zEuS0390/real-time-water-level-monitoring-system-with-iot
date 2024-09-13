# Use the latest version of the official Ubuntu image as the base
FROM ubuntu:latest

# Set the working directory inside the container to /webapp
WORKDIR /webapp

# Copy all files from the current directory to /webapp in the container
COPY . /webapp

# Update the package list to ensure we have the latest information on available packages
RUN apt-get update -y

# Install Python 3, pip, and the Python virtual environment package
RUN apt-get install python3-pip python3-venv -y

# Create a new Python virtual environment in the /venv directory
RUN python3 -m venv /venv

# Upgrade pip to the latest version within the virtual environment
RUN /venv/bin/pip install --upgrade pip

# Install the required Python packages listed in requirements.txt without using cache
RUN /venv/bin/pip install --no-cache-dir -r requirements.txt

# Expose port 5000 to allow communication to/from the container on that port
EXPOSE 5000

# Set the environment variable to ensure Python output is sent directly to the terminal
ENV PYTHONUNBUFFERED=1

# Define the command to run the application using Gunicorn with specified options
CMD ["/venv/bin/gunicorn", "--worker-class", "eventlet", "--workers", "1", "--bind", "0.0.0.0:5000", "wsgi:app"]

